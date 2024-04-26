// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStateInterface.h"
#include "GameCore.generated.h"

/**
 * 
 */

class AFloor;
class UPlayerHud;

UCLASS(Blueprintable)
class CUBERUNNER_API AGameCore : public AGameModeBase, public IGameStateInterface
{
	GENERATED_BODY()

public:
	AGameCore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual Void EndPlay(const EEndPlayerReason::Type EndPlayReason) override;

protected:
	FTimerHandle TimerHandle;

protected:
	UPROPERTY(BlueprintReadWrite)
	FTransform FloorAttachPoint;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentScore;

	UPROPERTY()
	int LastScoreUpdate;

	UPROPERTY(BlueprintReadWrite)
	bool IsWallSpawned;

	UPROPERTY()
	int ScoreThreshold;

	UPROPERTY(EditAnywhere, Category = "Other_Class_Ref", BlueprintReadWrite);
	TArray<AFloor *> Floors;

	UPROPERTY(EditAnywhere, Category = "Other_Class_Ref");
	TSubclassOf<AFloor> BPFloorRef;

	// widget class to spawn hud
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHud> PlayerHudClass;

	// the widget instance that i m using as my hud
	UPROPERTY()
	class UPlayerHud* PlayerHud;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADeathWall> DeathWallBlueprintRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACubePlayer> PlayerBlueprintRef;

protected:
	UFUNCTION(BlueprintCallable)
	void AddScore(int Score);

	UFUNCTION(BlueprintCallable)
	void UpdateGameState();

	UFUNCTION(BLueprintCallable)
	void AddFloor();

	UFUNCTION(BlueprintCallable)
	void ExtendFloor();

	UFUNCTION(BlueprintCallable)
	void InitTiles();

	UFUNCTION(BlueprintCallable)
	void InitUI();

	UFUNCTION()
	void InitializeLastScoreHitTimer();

	UFUNCTION()
	void UpdateLastScoreHitTimer();

	UFUNCTION()
	void SpawnWall();

	UFUNCTION()
	void IncreasePlayerSpeed();

public:
	void SetScore_Implementation(int Score) override;
	void CallExtendFloor_Implementation() override;
};
