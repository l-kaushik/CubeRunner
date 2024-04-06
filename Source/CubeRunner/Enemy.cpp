// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameCore.h"
#include "GameStateInterface.h"
#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName("SceneRoot"));
	RootComponent = SceneRoot;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	if (BoxCollision)
	{
		UE_LOG(LogTemp, Error, TEXT("BoxCollision for AEnemy is created"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to create BoxCollision for AEnemy in constructor"))
	}

	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	BoxCollision->SetupAttachment(SceneRoot);

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cube"));
	CubeMesh->SetupAttachment(BoxCollision);
}
// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBoxBeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to create BoxCollision for AEnemy! in BeginPlay"))
	}

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {

		auto GameMode = GetWorld()->GetAuthGameMode();
		if (GameMode && GameMode->Implements<UGameStateInterface>())
		{
			IGameStateInterface::Execute_SetScore(GameMode, -1);
		}

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Enemy"));
		
		// play sound at location [implement this function here]

		this->Destroy();
	}
}

