#pragma once

#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

class UVRInteractionMenuWidgetComponent;
class UVRTeleportMovementComponent;
class UVRInteractionRayComponent;
class UVRAnimationHandComponent;
class UVRWidgetInteractionComponent;
class UMotionControllerComponent;
class UCameraComponent;

UCLASS()
class VRDEMO_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UMotionControllerComponent> MotionControllerLeftAimComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRWidgetInteractionComponent> WidgetInteractionLeftComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UMotionControllerComponent> MotionControllerLeftGripComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRAnimationHandComponent> HandLeftComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UMotionControllerComponent> MotionControllerRightAimComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRInteractionRayComponent> InteractionRayComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UMotionControllerComponent> MotionControllerRightGripComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRAnimationHandComponent> HandRightComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRInteractionMenuWidgetComponent> InteractionMenuWidgetComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRPawn|Components")
	TObjectPtr<UVRTeleportMovementComponent> TeleportMovementComponent;
	
};
