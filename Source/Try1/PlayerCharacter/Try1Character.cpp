// Copyright Epic Games, Inc. All Rights Reserved.

#include "Try1Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Try1.h"
#include "InterfaceComponents/AnimationInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CharacterActionComponents/ClimbComponent/ClimbComponent.h"
#include "CharacterActionComponents/LineTraceComponent/LineTraceComponent.h"
ATry1Character::ATry1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(30.0f);
	

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	/*AttachedComponents*/
	ClimbComponent = CreateDefaultSubobject<UClimbComponent>(TEXT("ClimbComponent"));
	LineTraceComponent = CreateDefaultSubobject<ULineTraceComponent>(TEXT("LineTraceComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATry1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATry1Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATry1Character::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATry1Character::Look);
		
		//Running
		EnhancedInputComponent->BindAction(RunAction , ETriggerEvent::Triggered, this, &ATry1Character::DoRun);
		EnhancedInputComponent->BindAction(RunAction , ETriggerEvent::Completed, this, &ATry1Character::StopRun);
		
		//crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATry1Character::DoCrouch);
		
		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started ,this , &ATry1Character::Interact);
		
	}
	else
	{
		UE_LOG(LogTry1, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATry1Character::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerAnimInstance(); //setting animation Instance for player
	
}

void ATry1Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ATry1Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATry1Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ATry1Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATry1Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ATry1Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

#pragma region RunFunction
void ATry1Character::DoRun()
{
	if (!bisrunning)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Running"));
		GetCharacterMovement()->MaxWalkSpeed = PlayerRunSpeed;
		bisrunning = !bisrunning;
	}
}

void ATry1Character::StopRun()
{
	if (bisrunning)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("StopRunning"));
		GetCharacterMovement()->MaxWalkSpeed = PlayerNormalWalkSpeed;
		bisrunning = !bisrunning;
	}
}
#pragma endregion

void ATry1Character::DoCrouch()
{
	
	if (!bplayerCrouching)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("crouch"));
		Crouch();
		PlayerAnimationState = EPlayerCharacterState::Crouch;
		
	}else{
		
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("uncrouch"));
		
		bool canuncrouch  = UnCrouchObjectDection();
		
		if (canuncrouch)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("something detected still in crouch"));
			bplayerCrouching = !bplayerCrouching;
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("nothing detected uncrouch"));
			
			UnCrouch();
			PlayerAnimationState = EPlayerCharacterState::UnCrouch;
		}
	}
	bplayerCrouching = !bplayerCrouching;
	AnimationSetter(PlayerAnimationState); //setting Animation States
}


bool ATry1Character::UnCrouchObjectDection()
{
	FVector PlayerUpVector = GetCapsuleComponent()->GetUpVector();
	FVector PlayerStartLocation = GetCapsuleComponent()->GetRelativeLocation();
	FVector EndTraceLocation  =  (PlayerStartLocation + (PlayerUpVector*300));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), 
		PlayerStartLocation,
		EndTraceLocation, 
		TraceTypeQuery1 ,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResult , 
		true);
	
	return HitResult.bBlockingHit;
}

void ATry1Character::Interact()
{
	if (LineTraceComponent)
	{
		FVector PlayerStartLocation;
		FRotator PlayerRotation;
		GetController()->GetPlayerViewPoint(PlayerStartLocation , PlayerRotation);
		FVector EndLocation = PlayerStartLocation + (PlayerRotation.Vector().XAxisVector* 1000);
		
		FHitResult HitResult = LineTraceComponent->ShootInteractivetrace(PlayerStartLocation , EndLocation , 10.0f );
		if (HitResult.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Hitted Object"));
	
		}
	}

	
}

//Animation Player_ref Setter
#pragma  region SetAnimationInstance
void ATry1Character::SetPlayerAnimInstance()
{
	PlayerAnim_Ref = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("SettedAnimationInstance"));
		
}
#pragma endregion

//Animation Enum Setter
#pragma region AnimationStateSetter
void ATry1Character::AnimationSetter(EPlayerCharacterState PlayerPresentState)
{
	if (PlayerAnim_Ref != nullptr)
	{
		if (PlayerAnim_Ref->GetClass()->ImplementsInterface(UAnimationInterface::StaticClass()))
		{
			IAnimationInterface::Execute_ShareAnimationData(PlayerAnim_Ref , PlayerPresentState);
		}
	}else
	{
		SetPlayerAnimInstance();
	}
}
#pragma endregion 
