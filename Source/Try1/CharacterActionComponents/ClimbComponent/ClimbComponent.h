// Fill out your copyright notice in the Description page	 of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameActors/TaskActors/BaseGameObject.h"
#include "GameActors/TaskActors/ladder/LadderActor.h"
#include "ClimbComponent.generated.h"

class UGetOwnerOfComponent;
class ATry1Character;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRY1_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UClimbComponent();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGetOwnerOfComponent* GetOwnerComponent;
	UPROPERTY(VisibleAnywhere, Category = "Climb")
	ATry1Character* possessor;
	UPROPERTY(EditAnywhere, Category = "Climb")
	float HeightOfLadder;
	UPROPERTY(EditAnywhere, Category = "Climb")
	float heightOfPlayer;
	UPROPERTY(EditAnywhere, Category = "Climb")
	float RequiredHeightToClimb;
	
	TObjectPtr<ALadderActor> LadderRef;
	
	UFUNCTION(BlueprintCallable)
	void ClimbAction(ABaseGameObject* GameActor , FVector ImpactNormal);
	UFUNCTION(BlueprintCallable)
	void RecheckHeight();
	/*UFUNCTION()
	void MontageFinished(UAnimMontage* Montage, bool bInterrupted);
	*/
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
