#include "Interaction/Components/VRInteractionSensorComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRInteractionSensorComponent)

UVRInteractionSensorComponent::UVRInteractionSensorComponent() 
	: bDetectedActive(true)
{
}

UPrimitiveComponent* UVRInteractionSensorComponent::GetDetectedComponent() const
{
	return DetectedComponent.IsValid() ? DetectedComponent.Get() : nullptr;
}

UPrimitiveComponent* UVRInteractionSensorComponent::GetLastDetectedComponent() const
{
	return LastDetectedComponent.IsValid() ? LastDetectedComponent.Get() : nullptr;
}

bool UVRInteractionSensorComponent::IsDetectActive() const
{
	return bDetectedActive;
}

void UVRInteractionSensorComponent::ActivateDetect()
{
	bDetectedActive = true;
}

void UVRInteractionSensorComponent::DeactivateDetect()
{
	bDetectedActive = false;
}

void UVRInteractionSensorComponent::SetDetectComponent(UPrimitiveComponent* InDetectComponent)
{
	if (!bDetectedActive)
	{
		return;
	}
	
	if (InDetectComponent && InDetectComponent == DetectedComponent)
	{
		return;
	}
	
	if (DetectedComponent.IsValid())
	{
		LastDetectedComponent = DetectedComponent;
	}
	
	OnLostDetectComponent.Broadcast(GetDetectedComponent());
	DetectedComponent = InDetectComponent;
	
	if (InDetectComponent)
	{
		OnDetectComponent.Broadcast(InDetectComponent);
	}
}
