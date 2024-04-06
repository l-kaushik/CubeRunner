// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "GameCore.h"

AGameCore::AGameCore()
{
	// Setting Default Values
	CurrentScore = 0;
}

void AGameCore::AddScore(int Score)
{
	/*
		This function will add the incoming scores into current score	
	*/


	CurrentScore += Score;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%d"), CurrentScore));
}

void AGameCore::UpdateGameState()
{
	/*
		This funciton is responsible for changing game state depends upon score, if score goes below 0 then display the end screen else update the player's score and increase player movement speed
	*/

	if (CurrentScore < 0)
	{
		// DisplayEndScreen ()
	}
	else
	{
		//UpdateScore()

		// IncreasePlayerSpeed()
	}
}

void AGameCore::AddFloor()
{
	/*
		This function keeps track of number of floor spawned in world and manage them
	*/
	
	if (BPFloorRef)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator(0.f, 0.f, 0.f);
			FVector spawnLocation = FloorAttachPoint.GetLocation();

			AFloor* NewFloor = world->SpawnActor<AFloor>(BPFloorRef, spawnLocation, rotator, spawnParams);

			FloorAttachPoint = NewFloor->GetAttachPoint();

			Floors.Insert(NewFloor, Floors.Num());

		}
	}

}


void AGameCore::ExtendFloor()
{
	/*
		This function is responsible for extending and reducing the floor
	*/

	if (!IsWallSpawned)
	{
		AddFloor();

		if (Floors.Num() > 2)
		{
			AFloor* TempFloor = Floors[0];
			Floors.RemoveAt(0);
			TempFloor->Destroy();
		}
	}
}

// Interface function
void AGameCore::SetScore_Implementation(int Score)
{
	AddScore(Score);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("GameCore"));
}

void AGameCore::CallExtendFloor_Implementation()
{
	ExtendFloor();
}
