// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterState.h"
#include "Enums/PlayerCharacterClimbAnimationStates.h"

#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Try1Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UClimbComponent;
class ULineTraceComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ATry1Character : public ACharacter
{
	GENERATED_BODY()
#pragma  region Camera
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma  endregion 
	
#pragma  region Character_Movement
	
	/*Character Movement Speed*/
	UPROPERTY(EditAnywhere, Category= "CharacterMovement", meta = (AllowPrivateAccess = "true"))
	float PlayerRunSpeed = 550.0f;
	
	UPROPERTY(EditAnywhere, Category= "CharacterMovement", meta = (AllowPrivateAccess = "true"))
	float PlayerNormalWalkSpeed = 300.0f;

	
	
#pragma  endregion 
	
protected:
#pragma region Input_Actions
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;
	
	UPROPERTY(EditAnywhere, Category="Input")	
	UInputAction* CrouchAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
#pragma endregion
	
#pragma region AttachedComponents
	UClimbComponent* ClimbComponent;
	ULineTraceComponent* LineTraceComponent;
#pragma endregion
	
	UPROPERTY(EditAnywhere, Category="bools")
	bool bisrunning;
	
	UPROPERTY(EditAnywhere, Category="bools")
	bool bplayerCrouching;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Enums")
	EPlayerCharacterState PlayerAnimationState; 
	UPROPERTY(EditAnywhere, Category="Enums")
	EPlayerCharacterClimbAnimationStates ClimbAnimation;
	
	
	
	
	
	
	//UPROPERTY(EditAnywhere ,Category = "CharacterExtras")
	


public:

	/** Constructor */
	ATry1Character();	
		
	UPROPERTY(EditAnywhere, Category="bools")
	bool bIsOnLadder;
	UPROPERTY(EditAnywhere, Category= "bools")
	bool bisClimbInteracted;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category  = "bools")
	bool isClimbing;
	
	UPROPERTY(EditAnywhere , Blueprintable)
	UAnimMontage*AnimMontage;
	UPROPERTY(EditAnywhere , Blueprintable)
	UAnimInstance* PlayerAnim_Ref;

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual  void BeginPlay() override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void StopMovement();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	
	UFUNCTION()
	void ExitClimb();
	
	

	
	
	
#pragma region CustomInputActionFunctions
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoRun();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void StopRun();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoCrouch();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	bool UnCrouchObjectDection();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	void Interact();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void SetPlayerAnimInstance();
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void AnimationSetter(EPlayerCharacterState PlayerPresentState, EPlayerCharacterClimbAnimationStates PlayerAnimationClimbState);
	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteLedgeClimb();


#pragma endregion

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

