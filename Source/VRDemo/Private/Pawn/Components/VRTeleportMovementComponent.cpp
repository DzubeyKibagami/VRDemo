#include "Pawn/Components/VRTeleportMovementComponent.h"

#include "NavigationSystem.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Log/VRDemoLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRTeleportMovementComponent)

UVRTeleportMovementComponent::UVRTeleportMovementComponent() 
	: TeleportLaunchSpeed(650.f)
	, TeleportProjectileRadius(3.6f)
	, NavMeshCellHeight(8.f)
	, TeleportPredictDrawDebugType(EDrawDebugTrace::None)
	, TeleportPredictDrawDebugTime(1.f)
	, SnapTurnDegree(45.f)
	, bLastValidTeleportLocation(false)
{
}

void UVRTeleportMovementComponent::StartTeleportTrace()
{
	if (const auto TeleportTraceNiagara = GetTeleportTraceNiagaraComponent())
	{
		TeleportTraceNiagara->Activate();
		TeleportTraceNiagara->SetVisibility(true);
	}
}

void UVRTeleportMovementComponent::EndTeleportTrace()
{
	if (const auto TeleportTraceNiagara = GetTeleportTraceNiagaraComponent())
	{
		TeleportTraceNiagara->SetVisibility(false);
		TeleportTraceNiagara->Deactivate();
	}
	
	if (const auto TeleportVisualizer = GetTeleportVisualizerActor())
	{
		TeleportVisualizer->SetActorHiddenInGame(true);
	}
}

void UVRTeleportMovementComponent::TeleportTrace(const FVector& StartPosition, const FVector& ForwardVector)
{
	auto NavigationSystem = UNavigationSystemV1::GetCurrent(this);
	if (!NavigationSystem)
	{
		UE_LOG(LogVRDemo, Error, TEXT("NavigationSystem not found! Calculate teleport trace is not correct!"));
		return;
	}
	
	FHitResult OutHitResult;
	TArray<FVector> TracePathPositions;
	FVector OutLastTraceDestination;
	FVector LaunchVelocityVector = FVector(TeleportLaunchSpeed) * ForwardVector;
	TArray<AActor*> IgnoreActors;
	UGameplayStatics::Blueprint_PredictProjectilePath_ByObjectType(this, OutHitResult, TracePathPositions, 
		OutLastTraceDestination, StartPosition, LaunchVelocityVector, true, TeleportProjectileRadius, TeleportObjectTypeQueries, 
		false, IgnoreActors, TeleportPredictDrawDebugType, TeleportPredictDrawDebugTime);
	
	TracePathPositions.Insert(StartPosition, 0);
	
	FNavLocation OutLocation;
	bool bValidTeleportLocation = NavigationSystem->ProjectPointToNavigation(OutHitResult.Location, OutLocation, FVector::ZeroVector);
	
	ProjectedTeleportLocation = OutLocation.Location;
	ProjectedTeleportLocation.Z -= NavMeshCellHeight;
	
	const auto TeleportVisualizer = GetTeleportVisualizerActor();
	if (bValidTeleportLocation != bLastValidTeleportLocation)
	{
		bLastValidTeleportLocation = bValidTeleportLocation;
		if (TeleportVisualizer)
		{
			TeleportVisualizer->SetActorHiddenInGame(!bValidTeleportLocation);
		}
	}
	
	if (TeleportVisualizer && bValidTeleportLocation)
	{
		TeleportVisualizer->SetActorLocation(ProjectedTeleportLocation);
	}
	
	if (const auto TeleportTraceNiagaraComponent = GetTeleportTraceNiagaraComponent())
	{
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(TeleportTraceNiagaraComponent, TeleportPointPathParamName, TracePathPositions);
	}
}

void UVRTeleportMovementComponent::TryTeleport()
{
	if (!bLastValidTeleportLocation)
	{
		return;
	}
	
	if (const auto Camera = GetCachedOwnerCamera())
	{
		bLastValidTeleportLocation = false;
	
		FVector CameraRelativeLocation = Camera->GetRelativeLocation();
		CameraRelativeLocation.Z = 0;
		
		auto OwnerActor = GetOwner();
		auto OwnerActorRotation = OwnerActor->GetActorRotation();
		OwnerActorRotation.Pitch = 0;
		OwnerActorRotation.Roll = 0;
		
		OwnerActor->TeleportTo(ProjectedTeleportLocation - OwnerActorRotation.RotateVector(CameraRelativeLocation), OwnerActorRotation);
	}
}

void UVRTeleportMovementComponent::SnapTurn(const bool bRightTurn)
{
	const float YawDelta = bRightTurn ? SnapTurnDegree : -SnapTurnDegree;
	GetOwner()->AddActorWorldRotation(FRotator(0, YawDelta, 0));
}

UNiagaraComponent* UVRTeleportMovementComponent::GetTeleportTraceNiagaraComponent()
{
	if (TeleportTraceComponent)
	{
		return TeleportTraceComponent;
	}
	
	if (TeleportTraceNiagaraSystem.IsNull())
	{
		UE_LOG(LogVRDemo, Warning, TEXT("TeleportTraceNiagaraSystem is null! Teleport trace effect not created!"));
		return nullptr;
	}

	const auto AttachToComponent = GetOwner()->GetRootComponent();
	TeleportTraceComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TeleportTraceNiagaraSystem.LoadSynchronous(), AttachToComponent, NAME_None, 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, false);
	
	return TeleportTraceComponent;
}

AActor* UVRTeleportMovementComponent::GetTeleportVisualizerActor()
{
	if (IsValid(TeleportVisualizerActor))
	{
		return TeleportVisualizerActor;
	}
	
	if (TeleportVisualizerActorClass.IsNull())
	{
		UE_LOG(LogVRDemo, Warning, TEXT("TeleportVisualizerActorClass is null! Teleport target place actor not created!"));
		return nullptr;
	}
	
	TeleportVisualizerActor = GetWorld()->SpawnActor<AActor>(TeleportVisualizerActorClass.LoadSynchronous());
	TeleportVisualizerActor->SetActorHiddenInGame(true);
	return TeleportVisualizerActor;
}
