#pragma once

#include "VRMovementComponentBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VRTeleportMovementComponent.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class VRDEMO_API UVRTeleportMovementComponent : public UVRMovementComponentBase
{
	GENERATED_BODY()
	
public:
	UVRTeleportMovementComponent();
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRTeleportMovementComponent")
	void StartTeleportTrace();
	
	UFUNCTION(BlueprintCallable, Category = "VRTeleportMovementComponent")
	void EndTeleportTrace();
	
	UFUNCTION(BlueprintCallable, Category = "VRTeleportMovementComponent")
	void TeleportTrace(const FVector& StartPosition, const FVector& ForwardVector);
	
	UFUNCTION(BlueprintCallable, Category = "VRTeleportMovementComponent")
	void TryTeleport();
	
	UFUNCTION(BlueprintCallable, Category = "VRTeleportMovementComponent")
	void SnapTurn(const bool bRightTurn);
	
protected:
	UNiagaraComponent* GetTeleportTraceNiagaraComponent();
	AActor* GetTeleportVisualizerActor();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Visual")
	TSoftObjectPtr<UNiagaraSystem> TeleportTraceNiagaraSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Visual")
	TSoftClassPtr<AActor> TeleportVisualizerActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Visual")
	FName TeleportPointPathParamName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Predict")
	float TeleportLaunchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Predict")
	float TeleportProjectileRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Predict")
	float NavMeshCellHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Predict")
	TArray<TEnumAsByte<EObjectTypeQuery>> TeleportObjectTypeQueries;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Debug")
	TEnumAsByte<EDrawDebugTrace::Type> TeleportPredictDrawDebugType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport|Debug")
	float TeleportPredictDrawDebugTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turn")
	float SnapTurnDegree;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UNiagaraComponent> TeleportTraceComponent;
	
	UPROPERTY(Transient)
	TObjectPtr<AActor> TeleportVisualizerActor;
	
protected:
	bool bLastValidTeleportLocation;
	FVector ProjectedTeleportLocation;
	
};