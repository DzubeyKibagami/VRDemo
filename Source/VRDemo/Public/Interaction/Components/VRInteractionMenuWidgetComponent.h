#pragma once

#include "Components/WidgetComponent.h"
#include "VRInteractionMenuWidgetComponent.generated.h"

class UVRInteractionSensorComponent;

UCLASS()
class UVRInteractionMenuWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRInteractionMenuWidgetComponent")
	void Open();
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionMenuWidgetComponent")
	void Close();
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionMenuWidgetComponent")
	bool ToggleMenu();
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionMenuWidgetComponent")
	void SetLinkedSensor(UVRInteractionSensorComponent* SensorComponent);
	
protected:
	bool bIsMenuOpen;
	
};