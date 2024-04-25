// Fill out your copyright notice in the Description page of Project Settings.

#include "../GameObjects/Floor.h"
#include "../UIs/PlayerHud.h"
#include "../GameObjects/DeathWall.h"
#include "CubePlayerInterface.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "GameCore.h"

AGameCore::AGameCore()
{
	// Setting Default Values
	CurrentScore = 0;

	PlayerHudClass = nullptr;
	PlayerHud = nullptr;
}

void AGameCore::BeginPlay()
{
	Super::BeginPlay();

	InitTiles();
	InitUI();	
	InitializeLastScoreHitTimer();
}

//Void AGameCore::EndPlay(const EEndPlayerReason::Type EndPlayReason)
//{
//	if (PlayerHud)
//	{
//		PlayerHud->RemoveFromParent();
//		PlayerHud->nullptr;
//	}
//	
//	Super::EndPlay(EndPlayReason);
//}

void AGameCore::AddScore(int Score)
{
	/*
		This function will add the incoming scores into current score	
	*/


	CurrentScore += Score;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%d"), CurrentScore));

	// update game state
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
		PlayerHud->UpdateScore(CurrentScore);

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

void AGameCore::InitTiles()
{
	for (int i = 0; i <= 2; i++)
	{
		AddFloor();
	}
}

void AGameCore::InitUI()
{
	APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	check(FPC);
	PlayerHud = CreateWidget<UPlayerHud>(FPC, PlayerHudClass);
	check(PlayerHud);
	PlayerHud->AddToPlayerScreen();
	PlayerHud->UpdateScore(0);
}

void AGameCore::InitializeLastScoreHitTimer()
{
	if (!IsWallSpawned)
	{
		LastScoreUpdate = 0;

		// update time
		PlayerHud->UpdateTime(LastScoreUpdate);

		FTimerHandle TimerHandle;

		// set timer to call function after a delay
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameCore::UpdateLastScoreHitTimer, 1.0f, true);
	}
}

void AGameCore::UpdateLastScoreHitTimer()
{
	if (LastScoreUpdate > 10)
	{
		SpawnWall();
		PlayerHud->UpdateTime(-1);
		IsWallSpawned = true;
	}
	else
	{
		PlayerHud->UpdateTime(LastScoreUpdate);
		LastScoreUpdate++;
	}
}

void AGameCore::SpawnWall()
{
	if (!IsWallSpawned)
	{
		if (DeathWallBlueprintRef)
		{
			UWorld* world = GetWorld();
			if (world)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				spawnParams.Owner = this;

				FRotator rotator(FloorAttachPoint.GetRotation());

				ADeathWall* DeathWall = world->SpawnActor<ADeathWall>(DeathWallBlueprintRef, FloorAttachPoint.GetLocation(), rotator, spawnParams);
			}
		}
	}
}

void AGameCore::IncreasePlayerSpeed()
{
	/*
	* This function increase player speed according to current score value
	*/

	if (CurrentScore > ScoreThreshold)
	{	
		/*
		* Increase player speed by 200 on every 10 points
		*/

		auto GameMode = GetWorld()->GetAuthGameMode();
		if (GameMode && GameMode->Implements<UCubePlayerInterface>())
		{
			ICubePlayerInterface::Execute_SetDeltaLocationX(GameMode,ICubePlayerInterface::Execute_GetDeltaLocationX(GameMode) + 200.0f);

			ScoreThreshold += 10;

			InitializeLastScoreHitTimer();
		}
	}
	else
	{
		InitializeLastScoreHitTimer();
	}
}

// Interface function
void AGameCore::SetScore_Implementation(int Score)
{
	AddScore(Score);
}

void AGameCore::CallExtendFloor_Implementation()
{
	ExtendFloor();
}
