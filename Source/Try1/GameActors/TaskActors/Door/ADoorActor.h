// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActors/TaskActors/BaseGameObject.h"
#include "ADoorActor.generated.h"

class UBoxComponent;
UCLASS()
class TRY1_API AADoorActor : public ABaseGameObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AADoorActor();
	UPROPERTY(EditAnywhere , Blueprintable)
	UStaticMeshComponent* DoorFrame;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* TriggerBox;
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void  DoorAnimationImplementation();
	virtual void InteractInterface_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
