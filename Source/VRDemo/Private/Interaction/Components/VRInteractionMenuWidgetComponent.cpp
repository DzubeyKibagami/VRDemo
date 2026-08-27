#include "Interaction/Components/VRInteractionMenuWidgetComponent.h"

#include "Interaction/UI/VRInteractionObjectsWidget.h"

void UVRInteractionMenuWidgetComponent::Open()
{
	if (auto InteractionObjectsWidget = Cast<UVRInteractionObjectsWidget>(GetUserWidgetObject()))
	{
		InteractionObjectsWidget->SetVisibility(ESlateVisibility::Visible);
		bIsMenuOpen = true;
	}
}

void UVRInteractionMenuWidgetComponent::Close()
{
	if (auto InteractionObjectsWidget = Cast<UVRInteractionObjectsWidget>(GetUserWidgetObject()))
	{
		InteractionObjectsWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsMenuOpen = false;
	}
}

bool UVRInteractionMenuWidgetComponent::ToggleMenu()
{
	if (bIsMenuOpen)
	{
		Close();
		return false;
	}
	else
	{
		Open();
		return true;
	}
}

void UVRInteractionMenuWidgetComponent::SetLinkedSensor(UVRInteractionSensorComponent* SensorComponent)
{
	if (auto InteractionObjectsWidget = Cast<UVRInteractionObjectsWidget>(GetUserWidgetObject()))
	{
		InteractionObjectsWidget->SetLinkedSensor(SensorComponent);
	}
}
