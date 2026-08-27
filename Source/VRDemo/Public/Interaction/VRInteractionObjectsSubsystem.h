#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "VRInteractionObjectsSubsystem.generated.h"

UCLASS()
class UVRInteractionObjectsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	static UVRInteractionObjectsSubsystem* Get(const UObject* WorldContextObject);
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsSubsystem")
	void RegisterObject(UObject* Object);
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsSubsystem")
	void UnregisterObject(UObject* Object);
	
	UFUNCTION(BlueprintCallable, Category = "VRInteractionObjectsSubsystem")
	int32 GetObjectCount() const;
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectCountChangedDelegate, const int32, NewCount);
	UPROPERTY(BlueprintAssignable)
	FOnObjectCountChangedDelegate OnObjectCountChanged;
	
protected:
	TArray<TWeakObjectPtr<UObject>> InteractionObjects;
	
};