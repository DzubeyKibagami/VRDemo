#pragma once

#include "Blueprint/UserWidget.h"
#include "Interaction/Data/VRInteractionObjectData.h"
#include "VRInteractionObjectsWidget.generated.h"

class UVRInteractionSensorComponent;

UCLASS()
class VRDEMO_API UVRInteractionObjectsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsWidget")
	void SetLinkedSensor(UVRInteractionSensorComponent* SensorComponent);
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsWidget")
	void RequestAddActorByFocusedObject(const FVector& Location, const FRotator& Rotation);
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsWidget")
	void RequestRemoveFocusedObject();
	
protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName =  "OnUpdateFocusObjectData", Category = "VRInteractionObjectsWidget")
	void ReceiveUpdateFocusObjectData(const FVRInteractionObjectData& Data);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName =  "OnUpdateObjectsCount", Category = "VRInteractionObjectsWidget")
	void ReceiveUpdateObjectsCount(int32 NewCount);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName =  "OnObjectLostFocus", Category = "VRInteractionObjectsWidget")
	void ReceiveObjectLostFocus();
	
protected:
	UFUNCTION()
	void HandleDetectComponent(UPrimitiveComponent* Component);
	
	UFUNCTION()
	void HandleLostDetectComponent(UPrimitiveComponent* Component);
	
	UFUNCTION()
	void HandleObjectCountChanged(const int NewCount);
	
protected:
	TWeakObjectPtr<UVRInteractionSensorComponent> LinkedSensor;
	
};
