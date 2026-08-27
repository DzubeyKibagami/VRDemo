#pragma once

#include "CoreMinimal.h"
#include "VRInteractionObjectData.generated.h"

UENUM()
enum class EInteractionObjectType : uint8
{
	None,
	Cube,
	Sphere,
	Cylinder,
	Cone
};

USTRUCT(BlueprintType)
struct FVRInteractionObjectData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInteractionObjectType ObjectType = EInteractionObjectType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
	
};