#include "Pawn/Components/Animation/VRHandAnimInstance.h"

#include "Log/VRDemoLog.h"
#include "Pawn/Components/VRAnimationHandComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRHandAnimInstance)

void UVRHandAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (const auto VRAnimationHandComponent =  Cast<UVRAnimationHandComponent>(GetOwningComponent()))
	{
		bMirror = VRAnimationHandComponent->IsMirror();
	}
	else
	{
		UE_LOG(LogVRDemo, Error, TEXT("Owning component is not UVRAnimationHandComponent! bMiror variable is not set automatically. Please set it manually."));
	}
}
