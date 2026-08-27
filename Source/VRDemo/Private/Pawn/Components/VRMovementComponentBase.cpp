#include "Pawn/Components/VRMovementComponentBase.h"

#include "Camera/CameraComponent.h"
#include "Log/VRDemoLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRMovementComponentBase)

UCameraComponent* UVRMovementComponentBase::GetCachedOwnerCamera()
{
	if (OwnerCamera.IsValid())
	{
		return OwnerCamera.Get();
	}
	
	if (const auto OwnerActor = GetOwner())
	{
		OwnerCamera = OwnerActor->FindComponentByClass<UCameraComponent>();
		return OwnerCamera.IsValid() ? OwnerCamera.Get() : nullptr;
	}
	
	UE_LOG(LogVRDemo, Error, TEXT("OwnerCamera is not found! Movement operations may be not correct!"));
	return nullptr;
}
