#include "Interaction/UI/VRInteractionObjectsWidget.h"

#include "Interaction/VRInteractionObjectsSubsystem.h"
#include "Interaction/VRInteractionStatics.h"
#include "Interaction/Components/VRInteractionSensorComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VRInteractionObjectsWidget)

void UVRInteractionObjectsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (auto InteractionObjectsSubsystem = UVRInteractionObjectsSubsystem::Get(this))
	{
		InteractionObjectsSubsystem->OnObjectCountChanged.AddDynamic(this, &ThisClass::HandleObjectCountChanged);
		ReceiveUpdateObjectsCount(InteractionObjectsSubsystem->GetObjectCount());
	}
}

void UVRInteractionObjectsWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (auto InteractionObjectsSubsystem = UVRInteractionObjectsSubsystem::Get(this))
	{
		InteractionObjectsSubsystem->OnObjectCountChanged.RemoveAll(this);
	}
}

void UVRInteractionObjectsWidget::SetLinkedSensor(UVRInteractionSensorComponent* SensorComponent)
{
	LinkedSensor = SensorComponent;
	if (SensorComponent)
	{
		SensorComponent->OnDetectComponent.AddUniqueDynamic(this, &ThisClass::HandleDetectComponent);
		SensorComponent->OnLostDetectComponent.AddUniqueDynamic(this, &ThisClass::HandleLostDetectComponent);
	}
}

void UVRInteractionObjectsWidget::RequestAddActorByFocusedObject(const FVector& Location, const FRotator& Rotation)
{
	if (!LinkedSensor.IsValid())
	{
		return;
	}
	
	auto DetectComponent = LinkedSensor->GetDetectedComponent();
	if (!DetectComponent)
	{
		return;
	}
	
	auto OwnerFocusedActor = DetectComponent->GetOwner();
	if (IsValid(OwnerFocusedActor))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		SpawnTransform.SetScale3D(OwnerFocusedActor->GetActorScale());
		
		UVRInteractionStatics::TrySpawnInteractionActor(this, OwnerFocusedActor->GetClass(), SpawnTransform);
	}

}

void UVRInteractionObjectsWidget::RequestRemoveFocusedObject()
{
	if (!LinkedSensor.IsValid())
	{
		return;
	}
	
	auto DetectComponent = LinkedSensor->GetDetectedComponent();
	if (!DetectComponent)
	{
		return;
	}
	
	if (const auto InteractionObject = UVRInteractionStatics::GetInteractionObject(DetectComponent))
	{
		IVRInteractionObjectInterface::Execute_Delete(InteractionObject.GetObject());
	}
}

void UVRInteractionObjectsWidget::HandleDetectComponent(UPrimitiveComponent* Component)
{
	if (const auto InteractionObject = UVRInteractionStatics::GetInteractionObject(Component))
	{
		FVRInteractionObjectData ObjectData;
		IVRInteractionObjectInterface::Execute_GetData(InteractionObject.GetObject(), ObjectData);
		ReceiveUpdateFocusObjectData(ObjectData);	
	}
}

void UVRInteractionObjectsWidget::HandleLostDetectComponent(UPrimitiveComponent* Component)
{
	ReceiveObjectLostFocus();
}

void UVRInteractionObjectsWidget::HandleObjectCountChanged(const int NewCount)
{
	ReceiveUpdateObjectsCount(NewCount);
}
