// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Algo/RandomShuffle.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "Enemy.h"
#include "SafeCube.h"
#include "../GameModeAndInterfaces/GameCore.h"
#include "../GameModeAndInterfaces/GameStateInterface.h"
#include "Floor.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitVariables();

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::InitVariables()
{
	LanePositions = { -200.f, 0.f, 200.f };
}

void AFloor::InitEnemySpawnLocations()
{
	/*
		This function is responsible for generating spawn points
		
		An arrow component is getting spawned on the floor, then storing its relative location in an array

	*/

	int index = 0;

	for (float eachLane : LanePositions) {
		for (int i = 0; i < 12; i++) {

			// Spawn an arrow component and store its world transform in SpawnLocations

			UArrowComponent* ArrowComponent = NewObject<UArrowComponent>(this);
			if (ArrowComponent) {
				ArrowComponent->SetupAttachment(RootComponent);
				ArrowComponent->SetRelativeTransform(FTransform(FVector(i * 400, eachLane, 30.f)));

				SpawnLocations.Insert(ArrowComponent->GetComponentTransform(), index);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to create an Arrow Component at %d"), index);
			}

			index++;
		}
	}
}

void AFloor::SpawnEnemy()
{
	/*
		* Shuffling the spawnpoint locations,
		* while spawning the cube there is 70% of spawning Red Cube and 30% for blue
		* storing the object references of spawned cubes
	*/

	TArray<FTransform> RandomSpawnPoint = SpawnLocations;
	Algo::RandomShuffle(RandomSpawnPoint);

	for (int32 i = 0; i < 36; i++)
	{
		int TempSwitchVar = UKismetMathLibrary::RandomIntegerInRange(1, 10) > 7;
		switch (TempSwitchVar)
		{
			case 0: 
			{
				if (EnemyCubeBlueprintClass)
				{
					UWorld* world = GetWorld();
					if (world)
					{
						FActorSpawnParameters spawnParams;
						spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						spawnParams.Owner = this;

						FRotator rotator(0.f, 0.f, 0.f);
						FVector spawnLocation = RandomSpawnPoint[i].GetLocation();
						
						AEnemy* Cube = world->SpawnActor<AEnemy>(EnemyCubeBlueprintClass, spawnLocation, rotator, spawnParams);

						AllCubesRef.Insert(Cube, AllCubesRef.Num());
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to create an enemy cube"));
				}
				break;
			}
			case 1:
			{
				if (SafeCubeBlueprintClass)
				{
					UWorld* world = GetWorld();
					if (world)
					{
						FActorSpawnParameters spawnParams;
						spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						spawnParams.Owner = this;

						FRotator rotator(0.f, 0.f, 0.f);
						FVector spawnLocation = RandomSpawnPoint[i].GetLocation();

						AEnemy* Cube = world->SpawnActor<AEnemy>(SafeCubeBlueprintClass, spawnLocation, rotator, spawnParams);

						AllCubesRef.Insert(Cube, AllCubesRef.Num());
					}
				}
			}
		}
	}
}

void AFloor::ExtendFloorTrigger(AActor* OtherActor)
{
	// Responsible for spawning, removing floors and removing cubes

	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) 
	{
		auto GameMode = GetWorld()->GetAuthGameMode();
		if (GameMode && GameMode->Implements<UGameStateInterface>())
		{
			IGameStateInterface::Execute_CallExtendFloor(GameMode);

			// Destroy all cubes
			for (auto cube : AllCubesRef)
			{
				cube->Destroy();
			}
		}
	}
}

void AFloor::OutOfBoundTrigger(AActor* OtherActor)
{
	// This function will get trigger when player goes out of the floor

	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "create end ui");

		// Create End UI
	}
}

