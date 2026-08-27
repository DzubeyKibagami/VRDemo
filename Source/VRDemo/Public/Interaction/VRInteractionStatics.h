#pragma once

#include "Interfaces/VRInteractionObjectInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VRInteractionStatics.generated.h"

UENUM(BlueprintType)
enum class EVRDemoCastResult : uint8
{
	Valid,
	NotValid
};

UCLASS()
class VRDEMO_API UVRInteractionStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Branches"), Category = "VRInteractionStatics")
	static void TryGetInteractionObject(UPrimitiveComponent* Component, EVRDemoCastResult& Branches, TScriptInterface<IVRInteractionObjectInterface>& Object);
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionStatics")
	static TScriptInterface<IVRInteractionObjectInterface> GetInteractionObject(UPrimitiveComponent* Component);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "VRInteractionStatics")
	static bool TrySpawnInteractionActor(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& Transform);
	
};