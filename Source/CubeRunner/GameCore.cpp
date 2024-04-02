// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore.h"

AGameCore::AGameCore()
{
	// Setting Default Values
	CurrentScore = 0;
}

void AGameCore::AddScore(int Score)
{
	CurrentScore += Score;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%d"), CurrentScore));
}

void AGameCore::SetScore_Implementation(int Score)
{
	AddScore(Score);
}
