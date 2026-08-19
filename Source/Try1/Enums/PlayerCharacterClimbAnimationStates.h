#pragma once
#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EPlayerCharacterClimbAnimationStates : uint8
{
	None UMETA(DisplayName = "None"),
	climbIdle UMETA(DisplayName = "ClimbIdle"),
	climbup  UMETA(DisplayName = "Climbup"),
	climbdown UMETA(DisplayName = "Climbdown"),
};