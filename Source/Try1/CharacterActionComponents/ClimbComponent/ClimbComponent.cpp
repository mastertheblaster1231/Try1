// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "CharacterActionComponents/GettingOwnerComponent/GetOwnerOfComponent.h"

// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	GetOwnerComponent = CreateDefaultSubobject<UGetOwnerOfComponent>("GetOwnerComponent");

	// ...
}


void UClimbComponent::ClimbAction()
{
	if (possessor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("possessor is successfully possed"));
	}
}

// Called when the game starts
void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();
	possessor = GetOwnerComponent->GetOwnerComponentReference(GetOwner());
	if (possessor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("possessor is successfully possed"));
	}
 //getting Owner of Component
}


// Called every frame
void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

