#include "Pawn/Components/VRAnimationHandComponent.h"

#include "Log/VRDemoLog.h"
#include "Pawn/Components/Animation/VRHandAnimInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRAnimationHandComponent)

UVRAnimationHandComponent::UVRAnimationHandComponent() 
	: bMirror(false)
{
}

void UVRAnimationHandComponent::BeginPlay()
{
	Super::BeginPlay();
	
	HandAnimInstance = Cast<UVRHandAnimInstance>( GetAnimInstance());
	if (!HandAnimInstance.IsValid())
	{
		UE_LOG(LogVRDemo, Error, TEXT("Anim instance class is not UVRHandAnimInstance! Set pose functions is not work."));
	}
}

void UVRAnimationHandComponent::SetPoseAlphaGrasp(const float Value)
{
	if (HandAnimInstance.IsValid())
	{
		HandAnimInstance->PoseAlphaGrasp = Value;
	}
}

void UVRAnimationHandComponent::SetPoseAlphaIndexCurl(const float Value)
{
	if (HandAnimInstance.IsValid())
	{
		HandAnimInstance->PoseAlphaIndexCurl = Value;
	}
}

void UVRAnimationHandComponent::SetPoseAlphaIndexPoint(const float Value)
{
	if (HandAnimInstance.IsValid())
	{
		HandAnimInstance->PoseAlphaIndexPoint = Value;
	}
}

void UVRAnimationHandComponent::SetPoseAlphaThumbUp(const float Value)
{
	if (HandAnimInstance.IsValid())
	{
		HandAnimInstance->PoseAlphaThumbUp = Value;
	}
}

bool UVRAnimationHandComponent::IsMirror() const
{
	return bMirror;
}
