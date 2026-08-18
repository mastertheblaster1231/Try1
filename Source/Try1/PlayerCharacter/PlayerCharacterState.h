#pragma once
#include "CoreMinimal.h"
#include "PlayerCharacterState.generated.h"

UENUM(BlueprintType , DisplayName = "EPlayerCharacterState")
enum class EPlayerCharacterState : uint8
{
	None UMETA(DisplayName="None"),
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Runing UMETA(DisplayName = "Running"),
	Crouch UMETA(DisplayName = "Crouch"),
	ClimbIdle UMETA(DisplayName = "ClimbIdle"),
	ClimbUp UMETA(DisplayName = "ClimbUp"),
	ClimbDown UMETA(DisplayName = "ClimbDown"),
	UnCrouch UMETA(DisplayName = "UnCrouch"),
};