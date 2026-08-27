#pragma once

#include "Animation/AnimInstance.h"
#include "VRHandAnimInstance.generated.h"

UCLASS()
class VRDEMO_API UVRHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = "Anim poses")
	float PoseAlphaGrasp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = "Anim poses")
	float PoseAlphaIndexCurl;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = "Anim poses")
	float PoseAlphaIndexPoint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = "Anim poses")
	float PoseAlphaThumbUp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = "Anim poses")
	bool bMirror;
	
};