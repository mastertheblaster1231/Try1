// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameObject.h"


// Sets default values
ABaseGameObject::ABaseGameObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABaseGameObject::InteractInterface_Implementation()
{
	IInteractItemInterface::InteractInterface_Implementation();
	
}

// Called when the game starts or when spawned
void ABaseGameObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

