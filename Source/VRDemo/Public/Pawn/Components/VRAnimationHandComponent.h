#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "VRAnimationHandComponent.generated.h"

class UVRHandAnimInstance;

UCLASS()
class VRDEMO_API UVRAnimationHandComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UVRAnimationHandComponent();
	
public:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "VRAnimationHandComponent|Animation")
	void SetPoseAlphaGrasp(const float Value);
	
	UFUNCTION(BlueprintCallable, Category = "VRAnimationHandComponent|Animation")
	void SetPoseAlphaIndexCurl(const float Value);
	
	UFUNCTION(BlueprintCallable, Category = "VRAnimationHandComponent|Animation")
	void SetPoseAlphaIndexPoint(const float Value);
	
	UFUNCTION(BlueprintCallable, Category = "VRAnimationHandComponent|Animation")
	void SetPoseAlphaThumbUp(const float Value);
	
public:
	bool IsMirror() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Orientation")
	bool bMirror;
	
protected:
	TWeakObjectPtr<UVRHandAnimInstance> HandAnimInstance;
	
};