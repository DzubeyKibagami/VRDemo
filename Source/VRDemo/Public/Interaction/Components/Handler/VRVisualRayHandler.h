#pragma once

#include "CoreMinimal.h"
#include "VRVisualRayHandler.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

USTRUCT()
struct FVRVisualRayHandler
{
	GENERATED_BODY()
	
public:
	FVRVisualRayHandler();
	
public:
	void InitNiagaraSystemComponent(TSoftObjectPtr<UNiagaraSystem> NiagaraSystem, USceneComponent* AttachedComponent, const FName& InRayPointsParamName);
	void SetLength(const FVector& Start, const FVector& Forward, const float Length);
	void Start(const FVector& Start, const FVector& Forward, const float MaxLength);
	void Stop() const;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UNiagaraComponent> NiagaraSystemComponent;
	
protected:
	TArray<FVector> RayPoints;
	FName RayPointsParamName;
	
};