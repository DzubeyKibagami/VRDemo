#include "Interaction/VRInteractionObjectsSubsystem.h"

#include "Interaction/Interfaces/VRInteractionObjectInterface.h"
#include "Log/VRDemoLog.h"

UVRInteractionObjectsSubsystem* UVRInteractionObjectsSubsystem::Get(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		if (const UWorld* World = WorldContextObject->GetWorld())
		{
			return World->GetSubsystem<UVRInteractionObjectsSubsystem>();
		}
	}

	return nullptr;
}

void UVRInteractionObjectsSubsystem::RegisterObject(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogVRDemo, Warning, TEXT("Object is null! Register object is not complete!"));
		return;
	}
	
	if (!Object->GetClass()->ImplementsInterface(UVRInteractionObjectInterface::StaticClass()))
	{
		UE_LOG(LogVRDemo, Warning, TEXT("Object is not implement interaction interface! Register object is not complete!"));
		return;
	}

	InteractionObjects.Add(Object);
	OnObjectCountChanged.Broadcast(InteractionObjects.Num());
}

void UVRInteractionObjectsSubsystem::UnregisterObject(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogVRDemo, Warning, TEXT("Object is null! Unregister object is not complete!"));
		return;
	}
	
	if (!Object->GetClass()->ImplementsInterface(UVRInteractionObjectInterface::StaticClass()))
	{
		UE_LOG(LogVRDemo, Warning, TEXT("Object is not implement interaction interface! Unregister object is not complete!"));
		return;
	}
	
	InteractionObjects.Remove(Object);
	OnObjectCountChanged.Broadcast(InteractionObjects.Num());
}

int32 UVRInteractionObjectsSubsystem::GetObjectCount() const
{
	return InteractionObjects.Num();
}
