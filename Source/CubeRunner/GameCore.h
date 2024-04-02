// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStateInterface.h"
#include "GameCore.generated.h"

/**
 * 
 */
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

protected:
	UFUNCTION(BlueprintCallable)
	void AddScore(int Score);
public:
	void SetScore_Implementation(int Score) override;
};
