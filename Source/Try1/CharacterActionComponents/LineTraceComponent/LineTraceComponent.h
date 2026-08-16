// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterActionComponents/GettingOwnerComponent/GetOwnerOfComponent.h"
#include "Components/ActorComponent.h"
#include "LineTraceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRY1_API ULineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULineTraceComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGetOwnerOfComponent* GetOwnerComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* possessor;
	
	UFUNCTION(BlueprintCallable)
	FHitResult ShootInteractivetrace(FVector startLocation , FVector endLocation, float InteractivetraceSize);
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
