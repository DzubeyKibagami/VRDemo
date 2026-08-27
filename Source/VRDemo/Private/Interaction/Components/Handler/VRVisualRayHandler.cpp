#include "Interaction/Components/Handler/VRVisualRayHandler.h"

#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Log/VRDemoLog.h"

FVRVisualRayHandler::FVRVisualRayHandler()
{
	RayPoints.AddDefaulted(2);
}

void FVRVisualRayHandler::InitNiagaraSystemComponent(TSoftObjectPtr<UNiagaraSystem> NiagaraSystem,
	USceneComponent* AttachedComponent, const FName& InRayPointsParamName)
{
	if (NiagaraSystem.IsNull())
	{
		UE_LOG(LogVRDemo, Warning, TEXT("RayNiagaraSystem is null! Ray is not visualize!"));
		return;
	}

	NiagaraSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraSystem.LoadSynchronous(), AttachedComponent, NAME_None, 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
	
	RayPointsParamName = InRayPointsParamName;
}

void FVRVisualRayHandler::SetLength(const FVector& Start, const FVector& Forward, const float Length)
{
	if (NiagaraSystemComponent)
	{
		RayPoints[0] = Start;
		RayPoints[1] = Start + Forward * Length;
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(NiagaraSystemComponent, RayPointsParamName, RayPoints);
	}
}

void FVRVisualRayHandler::Start(const FVector& Start, const FVector& Forward, const float MaxLength)
{
	if (NiagaraSystemComponent)
	{
		NiagaraSystemComponent->Activate();
		SetLength(Start, Forward, MaxLength);
		NiagaraSystemComponent->SetVisibility(true);
	}
}

void FVRVisualRayHandler::Stop() const
{
	if (NiagaraSystemComponent)
	{
		NiagaraSystemComponent->SetVisibility(false);
		NiagaraSystemComponent->Deactivate();
	}
}
