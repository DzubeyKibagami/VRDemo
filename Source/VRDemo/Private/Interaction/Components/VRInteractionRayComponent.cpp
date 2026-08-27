#include "Interaction/Components/VRInteractionRayComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRInteractionRayComponent)

UVRInteractionRayComponent::UVRInteractionRayComponent() 
	: MaxRayLength(300.f)
	, TraceRayInterval(0.1f)
	, RayDebugTraceType(EDrawDebugTrace::None)
{
}

void UVRInteractionRayComponent::BeginPlay()
{
	Super::BeginPlay();
	VisualRayHandler.InitNiagaraSystemComponent(RayNiagaraSystem, this, RayPointParameterName);
	InnerActivate();
}

void UVRInteractionRayComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	InnerActivate();
}

void UVRInteractionRayComponent::Deactivate()
{
	Super::Deactivate();
	InnerDeactivate();
}

void UVRInteractionRayComponent::PerformTrace()
{
	FHitResult HitResult;
	const FVector& TraceStart = GetComponentLocation();
	const FVector& ComponentForwardVector = GetForwardVector();
	const FVector& TraceEnd = TraceStart + ComponentForwardVector * MaxRayLength;
	TArray<AActor*> IgnoreActors;
	if (UKismetSystemLibrary::LineTraceSingle(this, TraceStart, TraceEnd, RayTraceType, false, IgnoreActors, 
		RayDebugTraceType, HitResult, true))
	{
		VisualRayHandler.SetLength(TraceStart, ComponentForwardVector, HitResult.Distance);
		SetDetectComponent(HitResult.GetComponent());
	}
	else
	{
		VisualRayHandler.SetLength(TraceStart, ComponentForwardVector, MaxRayLength);
		SetDetectComponent(nullptr);
	}
}

void UVRInteractionRayComponent::InnerActivate()
{
	GetWorld()->GetTimerManager().SetTimer(RayTraceTimer, FTimerDelegate::CreateUObject(this, &UVRInteractionRayComponent::PerformTrace), TraceRayInterval, true);
	VisualRayHandler.Start(GetComponentLocation(), GetForwardVector(), MaxRayLength);
}

void UVRInteractionRayComponent::InnerDeactivate()
{
	GetWorld()->GetTimerManager().ClearTimer(RayTraceTimer);
	VisualRayHandler.Stop();
}
