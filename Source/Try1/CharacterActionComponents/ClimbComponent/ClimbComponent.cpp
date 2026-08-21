// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "CharacterActionComponents/GettingOwnerComponent/GetOwnerOfComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameActors/TaskActors/ladder/LadderActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter/Try1Character.h"

// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	GetOwnerComponent = CreateDefaultSubobject<UGetOwnerOfComponent>("GetOwnerComponent");

	// ...
}


void UClimbComponent::ClimbAction(ABaseGameObject* GameActor, FVector ImpactNormal)
{
	if (GameActor != nullptr)
	{
		possessor = Cast<ATry1Character>(GetOwner());
		
		
		HeightOfLadder = 0.0f;
		heightOfPlayer = 0.0f;
		RequiredHeightToClimb = 0.0f;
		
		if (possessor != nullptr && possessor->bisClimbInteracted){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("possessor is successfully possed"));
			
			if (LadderRef != nullptr)
			{
			//	possessor->GetCapsuleComponent()->SetWorldLocation(LadderRef->StartPlayerPostion->GetComponentLocation());
			}
			HeightOfLadder = GameActor->GetActorScale3D().Z*100.0f;
			heightOfPlayer = possessor->GetActorScale3D().Z*100.0f;
			RequiredHeightToClimb = HeightOfLadder-heightOfPlayer; 
			possessor->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			possessor->AnimationSetter(EPlayerCharacterState::Climb , EPlayerCharacterClimbAnimationStates::climbIdle); //AnimationState
			possessor->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			possessor->isClimbing = true;
			LadderRef  =  Cast<ALadderActor>(GameActor);
			if (LadderRef != nullptr)
			{
				RecheckHeight();
			}
		}
	}
}

void UClimbComponent::RecheckHeight()
{
	if(HeightOfLadder ==0.0f && heightOfPlayer == 0.0f&& RequiredHeightToClimb == 0.0f) return;
	
	
	if (LadderRef != nullptr && LadderRef->EndPlayerPostion != nullptr){

		if (possessor !=nullptr )
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Character_Climb Size: %f"),  possessor->GetActorLocation().Z));
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Wall_Climb Size: %f"),   RequiredHeightToClimb+20.0f));
		
	
			if ( possessor->GetActorLocation().Z >= LadderRef->EndPlayerPostion->GetComponentLocation().Z){
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("height Reached  Moveon!! "));	
				possessor->ExecuteLedgeClimb();
				possessor->GetCharacterMovement()->bUseControllerDesiredRotation = true;
				possessor->SetActorLocation(LadderRef->EndPlayerPostion->GetComponentLocation());
				possessor->AnimationSetter(EPlayerCharacterState::Idle, EPlayerCharacterClimbAnimationStates::None);
				possessor->isClimbing = false;
			}
		}	
	}
}
// Called when the game starts
void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

