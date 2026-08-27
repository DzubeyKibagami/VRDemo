#pragma once

#include "Components/ActorComponent.h"
#include "VRMovementComponentBase.generated.h"

class UCameraComponent;

UCLASS()
class VRDEMO_API UVRMovementComponentBase : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UCameraComponent* GetCachedOwnerCamera();

protected:
	TWeakObjectPtr<UCameraComponent> OwnerCamera;
	
};