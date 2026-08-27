#pragma once

#include "Components/SceneComponent.h"
#include "VRInteractionSensorComponent.generated.h"

UCLASS()
class VRDEMO_API UVRInteractionSensorComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UVRInteractionSensorComponent();
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRInteractionSensor")
	UPrimitiveComponent* GetDetectedComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionSensor")
	UPrimitiveComponent* GetLastDetectedComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionSensor")
	bool IsDetectActive() const;
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRInteractionSensor")
	void ActivateDetect();
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionSensor")
	void DeactivateDetect();
	
protected:
	void SetDetectComponent(UPrimitiveComponent* InDetectComponent);
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectComponentDelegate, UPrimitiveComponent*, Component);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDetectComponentDelegate OnDetectComponent;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLostDetectComponentDelegate, UPrimitiveComponent*, Component);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLostDetectComponentDelegate OnLostDetectComponent;
	
protected:
	TWeakObjectPtr<UPrimitiveComponent> DetectedComponent;
	TWeakObjectPtr<UPrimitiveComponent> LastDetectedComponent;
	bool bDetectedActive;
	
};