#include "Interaction/VRInteractionStatics.h"

void UVRInteractionStatics::TryGetInteractionObject(UPrimitiveComponent* Component, EVRDemoCastResult& Branches,
	TScriptInterface<IVRInteractionObjectInterface>& Object)
{
	Object = GetInteractionObject(Component);
	Branches = Object ? EVRDemoCastResult::Valid : EVRDemoCastResult::NotValid;
}

TScriptInterface<IVRInteractionObjectInterface> UVRInteractionStatics::GetInteractionObject(UPrimitiveComponent* Component)
{
	if (!Component)
	{
		return nullptr;
	}
	
	if (Component->GetClass()->ImplementsInterface(UVRInteractionObjectInterface::StaticClass()))
	{
		return Component;
	} 
	
	auto OwnerActor = Component->GetOwner();
	if (OwnerActor && OwnerActor->GetClass()->ImplementsInterface(UVRInteractionObjectInterface::StaticClass()))
	{
		return OwnerActor;
	}
	
	return nullptr;
}

bool UVRInteractionStatics::TrySpawnInteractionActor(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& Transform)
{
	if (!WorldContextObject)
	{
		return false;
	}
	
	if (!ActorClass)
	{
		return false;
	}
	
	if (!ActorClass->ImplementsInterface(UVRInteractionObjectInterface::StaticClass()))
	{
		return false;
	}
	
	if (const auto World = WorldContextObject->GetWorld())
	{
		if (const auto SpawnedActor = World->SpawnActor(ActorClass))
		{
			SpawnedActor->SetActorTransform(Transform);
			return true;
		}
	}
	
	return false;
}
