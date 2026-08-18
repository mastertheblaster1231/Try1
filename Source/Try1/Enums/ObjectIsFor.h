#pragma once
#include "CoreMinimal.h"
#include "ObjectIsFor.generated.h"

UENUM(BlueprintType)
enum class EObjectIsFor:uint8
{
	None UMETA(DisplayName = "None"),
	Climb UMETA(DisplayName="Climb"),
};