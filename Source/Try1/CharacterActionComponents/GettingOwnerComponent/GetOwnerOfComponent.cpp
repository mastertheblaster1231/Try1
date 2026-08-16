// Fill out your copyright notice in the Description page of Project Settings.


#include "GetOwnerOfComponent.h"


// Sets default values for this component's properties
UGetOwnerOfComponent::UGetOwnerOfComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGetOwnerOfComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AActor* UGetOwnerOfComponent::GetOwnerComponentReference(AActor* OwnerReference)
{
	AActor* ActorReference = Cast<AActor>(OwnerReference);
	return ActorReference;
}

// Called every frame
void UGetOwnerOfComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

