// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ArrowComponent.h"
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

