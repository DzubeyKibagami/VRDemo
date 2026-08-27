#include "Interaction/Components/VRWidgetInteractionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRWidgetInteractionComponent)

void UVRWidgetInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	VisualRayHandler.InitNiagaraSystemComponent(RayNiagaraSystem, this, RayPointParameterName);
}

void UVRWidgetInteractionComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	VisualRayHandler.Start(GetComponentLocation(), GetForwardVector(), InteractionDistance);
}

void UVRWidgetInteractionComponent::Deactivate()
{
	Super::Deactivate();
	VisualRayHandler.Stop();
}

UWidgetInteractionComponent::FWidgetTraceResult UVRWidgetInteractionComponent::PerformTrace() const
{
	const auto& Result = Super::PerformTrace();
	const_cast<UVRWidgetInteractionComponent*>(this)->VisualRayHandler.SetLength(GetComponentLocation(), GetForwardVector(), Result.HitResult.Distance);
	return Result;
}
