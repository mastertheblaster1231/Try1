// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderActor.h"
#include "Try1/PlayerCharacter/Try1Character.h"

// Sets default values
ALadderActor::ALadderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>("LadderMesh");
	StartBoxComp =  CreateDefaultSubobject<UBoxComponent>(TEXT("StartBoxCollision"));
	EndBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("EndBoxCollision"));
	
	StartPlayerPostion = CreateDefaultSubobject<USkeletalMeshComponent>("StartPlayerPostion");
	StartPlayerPostion->SetupAttachment(LadderMesh);	
	
	EndPlayerPostion = CreateDefaultSubobject<USkeletalMeshComponent>("EndPlayerPosition");
	EndPlayerPostion->SetupAttachment(LadderMesh);
	
	StartBoxComp->SetupAttachment(LadderMesh);
	EndBoxComp->SetupAttachment(LadderMesh);
}

// Called when the game starts or when spawned
void ALadderActor::BeginPlay()
{
	Super::BeginPlay();
	StartBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALadderActor::Start_BeginOverLap);
	StartBoxComp->OnComponentEndOverlap.AddDynamic(this, &ALadderActor::EndOverLap);
	
	EndBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALadderActor::End_BeginOverlap);
	EndBoxComp->OnComponentEndOverlap.AddDynamic(this, &ALadderActor::End_EndOverlap);
	
	
}
/*Begin Collision Box*/
void ALadderActor::Start_BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Start overlap"));
	ATry1Character* PlayerCharacter = Cast<ATry1Character>(OtherActor);
	FVector Location  = StartBoxComp->GetComponentLocation();
	
	
		if (PlayerCharacter)
		{
			PlayerCharacter->bisClimbInteracted = true;
		}
}

void ALadderActor::EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATry1Character* PlayerCharacter = Cast<ATry1Character>(OtherActor);
	
	
	if (PlayerCharacter && !PlayerCharacter->isClimbing)
	{
		PlayerCharacter->bisClimbInteracted = false;
	}

}

/*End Collision Box*/
void ALadderActor::End_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Start component Start overlap"));
	ATry1Character* PlayerCharacter = Cast<ATry1Character>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->bisClimbInteracted = false;
	}
	
}

void ALadderActor::End_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Endbox component Start overlap"));
	
}

void ALadderActor::climbTask(ATry1Character* playerCharacter)
{
	ATry1Character* PlayerCharacter =  Cast<ATry1Character>(playerCharacter);
	if (PlayerCharacter)
	{
		PlayerCharacter->bisClimbInteracted = true;
	}
}

// Called every frame
void ALadderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

