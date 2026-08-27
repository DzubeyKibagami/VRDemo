#pragma once

#include "Components/WidgetInteractionComponent.h"
#include "Handler/VRVisualRayHandler.h"
#include "VRWidgetInteractionComponent.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class VRDEMO_API UVRWidgetInteractionComponent : public UWidgetInteractionComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	
protected:
	virtual FWidgetTraceResult PerformTrace() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<UNiagaraSystem> RayNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	FName RayPointParameterName;
	
protected:
	UPROPERTY(Transient)
	FVRVisualRayHandler VisualRayHandler;
	
};