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

UCLASS(Blueprintable)
class CUBERUNNER_API AGameCore : public AGameModeBase, public IGameStateInterface
{
	GENERATED_BODY()

public:
	AGameCore();

protected:
	UPROPERTY(BlueprintReadWrite)
	FTransform FloorAttachPoint;

	UPROPERTY(BlueprintReadWrite)
	int CurrentScore;

	UPROPERTY(BlueprintReadWrite)
	bool IsWallSpawned;

	UPROPERTY(EditAnywhere, Category = "Other_Class_Ref", BlueprintReadWrite);
	TArray<AFloor *> Floors;

	UPROPERTY(EditAnywhere, Category = "Other_Class_Ref");
	TSubclassOf<AFloor> BPFloorRef;

protected:
	UFUNCTION(BlueprintCallable)
	void AddScore(int Score);

	UFUNCTION(BlueprintCallable)
	void UpdateGameState();

	UFUNCTION(BLueprintCallable)
	void AddFloor();

	UFUNCTION(BlueprintCallable)
	void ExtendFloor();

public:
	void SetScore_Implementation(int Score) override;
	void CallExtendFloor_Implementation() override;
};
