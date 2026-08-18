// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ObjectIsFor.h"
#include "GameFramework/Actor.h"
#include "InterfaceComponents/InteractItemInterface.h"
#include "BaseGameObject.generated.h"

UCLASS()
class TRY1_API ABaseGameObject : public AActor, public IInteractItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGameObject();
	
	UPROPERTY(EditAnywhere , Category ="Actor Settings")
	EObjectIsFor ObjectIsFor;
	
	virtual void InteractInterface_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
