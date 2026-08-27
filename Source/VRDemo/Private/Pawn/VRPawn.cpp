#include "Pawn/VRPawn.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "Interaction/Components/VRInteractionMenuWidgetComponent.h"
#include "Interaction/Components/VRInteractionRayComponent.h"
#include "Interaction/Components/VRWidgetInteractionComponent.h"
#include "Pawn/Components/VRAnimationHandComponent.h"
#include "Pawn/Components/VRTeleportMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRPawn)

AVRPawn::AVRPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("VROrigin");
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(RootComponent);
	
	MotionControllerLeftAimComponent = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerLeftAim");
	MotionControllerLeftAimComponent->MotionSource = "LeftAim";
	MotionControllerLeftAimComponent->SetupAttachment(RootComponent);
	
	WidgetInteractionLeftComponent = CreateDefaultSubobject<UVRWidgetInteractionComponent>("WidgetInteractionLeft");
	WidgetInteractionLeftComponent->SetupAttachment(MotionControllerLeftAimComponent);
	
	MotionControllerLeftGripComponent = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerLeftGrip");
	MotionControllerLeftGripComponent->MotionSource = "LeftGrip";
	MotionControllerLeftGripComponent->SetupAttachment(RootComponent);
	
	HandLeftComponent = CreateDefaultSubobject<UVRAnimationHandComponent>("HandLeft");
	HandLeftComponent->SetupAttachment(MotionControllerLeftGripComponent);
	
	MotionControllerRightAimComponent = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerRightAim");
	MotionControllerRightAimComponent->MotionSource = "RightAim";
	MotionControllerRightAimComponent->SetupAttachment(RootComponent);
	
	InteractionRayComponent = CreateDefaultSubobject<UVRInteractionRayComponent>("InteractionRay");
	InteractionRayComponent->SetupAttachment(MotionControllerRightAimComponent);
	
	MotionControllerRightGripComponent = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerRightGrip");
	MotionControllerRightGripComponent->MotionSource = "RightGrip";
	MotionControllerRightGripComponent->SetupAttachment(RootComponent);
	
	HandRightComponent = CreateDefaultSubobject<UVRAnimationHandComponent>("HandRight");
	HandRightComponent->SetupAttachment(MotionControllerRightGripComponent);
	
	InteractionMenuWidgetComponent = CreateDefaultSubobject<UVRInteractionMenuWidgetComponent>("InteractionMenuWidgetComponent");
	InteractionMenuWidgetComponent->SetupAttachment(HandRightComponent);
	
	TeleportMovementComponent = CreateDefaultSubobject<UVRTeleportMovementComponent>("VRMovement");
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::LocalFloor);
	}
}
