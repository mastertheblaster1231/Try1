// Fill out your copyright notice in the Description page of Project Settings.


#include "ADoorActor.h"
#include "Components/BoxComponent.h"


// Sets default values
AADoorActor::AADoorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrame");
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(DoorFrame);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	
}

void AADoorActor::InteractInterface_Implementation()
{
	Super::InteractInterface_Implementation();
	GEngine->AddOnScreenDebugMessage(-1 , 3.0f, FColor::Yellow, TEXT("DoorAction Running from Door interaface..."));
}

// Called when the game starts or when spawned
void AADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

