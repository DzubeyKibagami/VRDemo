#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/VRInteractionObjectInterface.h"
#include "VRSimpleInteractionActor.generated.h"

UCLASS()
class VRDEMO_API AVRSimpleInteractionActor : public AActor, public IVRInteractionObjectInterface
{
	GENERATED_BODY()
	
public:	
	AVRSimpleInteractionActor();

public:
	virtual void Hover_Implementation() override;
	virtual void UnHover_Implementation() override;
	virtual bool IsHovered_Implementation() override;
	virtual void Grab_Implementation(UPrimitiveComponent* AttachParentComponent) override;
	virtual void Release_Implementation() override;
	virtual bool IsGrabbed_Implementation() override;
	virtual void Delete_Implementation() override;
	virtual void Rotate_Implementation(float YawDelta, float PitchDelta, float Rate = 1) override;
	virtual void GetData_Implementation(FVRInteractionObjectData& OutData) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	void SetHighLight(float Value) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	FName MaterialHighLightParamName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	float MaterialHighLightPower;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FVRInteractionObjectData ObjectData;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> MaterialHighLightInstance;
	
protected:
	bool bIsHovered;
	bool bIsGrabbed;
	
};
