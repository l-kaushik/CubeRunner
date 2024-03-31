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
			SpawnLocations.Insert(FTransform(FVector(i * 400, eachLane, 0.f)), index);
			index++;
		}
	}
}

