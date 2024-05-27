// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScript.generated.h"

/**
 * 
 */
class ATriggerBox;
class UEndScreen;
class UOptionMenu;

UCLASS()
class CUBERUNNER_API ABaseLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelScript")
	ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Reference")
	TSubclassOf<UEndScreen> EndScreenRef;

private:
	UFUNCTION()
	void OnTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void LoadGameSettings();
};
