#pragma once

#include "CoreMinimal.h"
#include "Interaction/Data/VRInteractionObjectData.h"
#include "VRInteractionObjectInterface.generated.h"

UINTERFACE()
class UVRInteractionObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class IVRInteractionObjectInterface 
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void Hover();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void UnHover();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void Grab(UPrimitiveComponent* AttachParentComponent);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void Release();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void Rotate(float YawDelta, float PitchDelta, float Rate = 1);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void Delete();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	bool IsHovered();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	bool IsGrabbed();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractionObjectInterface")
	void GetData(FVRInteractionObjectData& OutData);
	
};
