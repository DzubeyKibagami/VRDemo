#include "Interaction/VRSimpleInteractionActor.h"

#include "Interaction/VRInteractionObjectsSubsystem.h"
#include "Log/VRDemoLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRSimpleInteractionActor)

AVRSimpleInteractionActor::AVRSimpleInteractionActor() 
	: MaterialHighLightPower(0.5f)
	, bIsHovered(false)
	, bIsGrabbed(false)
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetSingleSampleShadowFromStationaryLights(true);
}

void AVRSimpleInteractionActor::Hover_Implementation()
{
	SetHighLight(MaterialHighLightPower);
	bIsHovered = true;
}

void AVRSimpleInteractionActor::UnHover_Implementation()
{
	SetHighLight(0);
	bIsHovered = false;
}

bool AVRSimpleInteractionActor::IsHovered_Implementation()
{
	return bIsHovered;
}

void AVRSimpleInteractionActor::Grab_Implementation(UPrimitiveComponent* AttachParentComponent)
{
	if (!AttachParentComponent)
	{
		UE_LOG(LogVRDemo, Error, TEXT("ParentComponent is null. Grab is not start!"));
		return;
	}
	
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->AttachToComponent(AttachParentComponent, FAttachmentTransformRules::KeepWorldTransform);
	bIsGrabbed = true;
}

void AVRSimpleInteractionActor::Release_Implementation()
{
	if (!bIsGrabbed)
	{
		return;
	}
	
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	bIsGrabbed = false;
}

bool AVRSimpleInteractionActor::IsGrabbed_Implementation()
{
	return bIsGrabbed;
}

void AVRSimpleInteractionActor::Delete_Implementation()
{
	Destroy();
}

void AVRSimpleInteractionActor::Rotate_Implementation(float YawDelta, float PitchDelta, float Rate)
{
	FRotator DeltaRotation(PitchDelta * Rate, YawDelta * Rate, 0.0f);
	AddActorLocalRotation(DeltaRotation.Quaternion());
}

void AVRSimpleInteractionActor::GetData_Implementation(FVRInteractionObjectData& OutData)
{
	OutData = ObjectData;
}

void AVRSimpleInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (const auto Material = StaticMeshComponent->GetMaterial(0))
	{
		MaterialHighLightInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0, Material);
	}
	
	if (const auto InteractionObjectsSubsystem = UVRInteractionObjectsSubsystem::Get(this))
	{
		InteractionObjectsSubsystem->RegisterObject(this);
	}
}

void AVRSimpleInteractionActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (EndPlayReason == EEndPlayReason::Type::Destroyed || EndPlayReason == EEndPlayReason::RemovedFromWorld)
	{
		if (const auto InteractionObjectsSubsystem = UVRInteractionObjectsSubsystem::Get(this))
		{
			InteractionObjectsSubsystem->UnregisterObject(this);
		}
	}
}

void AVRSimpleInteractionActor::SetHighLight(float Value) const
{
	if (MaterialHighLightInstance)
	{
		MaterialHighLightInstance->SetScalarParameterValue(MaterialHighLightParamName, Value);
	}
}
