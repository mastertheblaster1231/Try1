// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameActors/TaskActors/BaseGameObject.h"
#include "LadderActor.generated.h"

class ATry1Character;

UCLASS()
class TRY1_API ALadderActor : public ABaseGameObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALadderActor();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LadderMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* StartBoxComp;
	UPROPERTY(EditAnywhere)
	UBoxComponent* EndBoxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> StartPlayerPostion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> EndPlayerPostion;
	
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void Start_BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void End_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void  End_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void climbTask(ATry1Character* PlayerCharacter);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
