// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTraceComponent.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
ULineTraceComponent::ULineTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	GetOwnerComponent = CreateDefaultSubobject<UGetOwnerOfComponent>("GetOwnerComponent");

	// ...
}


FHitResult ULineTraceComponent::ShootInteractivetrace(FVector startLocation, FVector endLocation, float InteractivetraceSize)
{
	FVector StartLocation = startLocation;
	FVector EndLocation= endLocation;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(possessor);
	FHitResult HitResult;
	if (possessor != nullptr)
	{
		UKismetSystemLibrary::SphereTraceSingle(possessor->GetWorld() , 
			StartLocation,
			EndLocation,
			10.0f,
			TraceTypeQuery1,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true
			);
	}
	return HitResult;	
}

// Called when the game starts
void ULineTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	possessor = GetOwnerComponent->GetOwnerComponentReference(GetOwner());
	if (possessor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "UGetOwnerComponent::BeginPlay() is working actually");
	}

	// ...
}


// Called every frame
void ULineTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

