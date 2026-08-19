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
	Climb UMETA(DisplayName = "Climb"),
	UnCrouch UMETA(DisplayName = "UnCrouch"),
};