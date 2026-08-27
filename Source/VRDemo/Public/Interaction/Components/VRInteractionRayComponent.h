#pragma once

#include "VRInteractionSensorComponent.h"
#include "Handler/VRVisualRayHandler.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VRInteractionRayComponent.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class VRDEMO_API UVRInteractionRayComponent : public UVRInteractionSensorComponent
{
	GENERATED_BODY()
	
public:
	UVRInteractionRayComponent();

public:
	virtual void BeginPlay() override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	
protected:
	void InnerActivate();
	void InnerDeactivate();
	void PerformTrace();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<UNiagaraSystem> RayNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	FName RayPointParameterName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Core")
	float MaxRayLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Core")
	float TraceRayInterval;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Core")
	TEnumAsByte<ETraceTypeQuery> RayTraceType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Core")
	TEnumAsByte<EDrawDebugTrace::Type> RayDebugTraceType;

protected:
	UPROPERTY(Transient)
	FVRVisualRayHandler VisualRayHandler;
	
protected:
	FTimerHandle RayTraceTimer;
	
};