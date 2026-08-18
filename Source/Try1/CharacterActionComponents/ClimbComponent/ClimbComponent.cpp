// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "CharacterActionComponents/GettingOwnerComponent/GetOwnerOfComponent.h"
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
			 HeightOfLadder = GameActor->GetActorScale3D().Z*100.0f;
			 heightOfPlayer = possessor->GetActorScale3D().Z*100.0f;
			 RequiredHeightToClimb = HeightOfLadder-heightOfPlayer; 
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Climb Size: %f"), heightOfPlayer));
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Climb Size: %f"), RequiredHeightToClimb));	
			possessor->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			possessor->GetCharacterMovement()->GravityScale = 0.0f;
			possessor->isClimbing = true;
			RecheckHeight();
		}
	}
}

void UClimbComponent::RecheckHeight()
{
	
	 if(HeightOfLadder ==0.0f && heightOfPlayer == 0.0f&& RequiredHeightToClimb == 0.0f) return;

	if (possessor !=nullptr )
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Character_Climb Size: %f"),  possessor->GetActorLocation().Z));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Wall_Climb Size: %f"),   RequiredHeightToClimb+190.0f));
		
	
		if ( possessor->GetActorLocation().Z > RequiredHeightToClimb +190.0f){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("height Reached  Moveon!! "));
			possessor->GetCharacterMovement()->StopMovementImmediately();
			/*FVector GetEdge = FVector(0.0f , 0.0f, 200.0f);
			possessor->GetCharacterMovement()->AddForce(GetEdge);*/
			possessor->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			possessor->GetCharacterMovement()->GravityScale = 1.0f;
			possessor->isClimbing = false;
			
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

