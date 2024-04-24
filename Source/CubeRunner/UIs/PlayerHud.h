// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNER_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// update score on hud
	void UpdateScore(int32 Score);

	// update timer on hud
	void UpdateTime(int32 Time);
	
	// widget to display score
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UEditableText* PlayerScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableText* LastScoreHitTimer;
};
