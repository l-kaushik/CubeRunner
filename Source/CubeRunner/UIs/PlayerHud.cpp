// Fill out your copyright notice in the Description page of Project Settings.


#include "kismet/KismetStringLibrary.h"
#include "kismet/KismetTextLibrary.h"
#include "Components/EditableText.h"
#include "PlayerHud.h"

void UPlayerHud::UpdateScore(int32 Score)
{
	if (PlayerScore)
	{
		//FString FirstPart = "Score: ";
		//PlayerScore->SetText(UKismetTextLibrary::Conv_StringToText((FirstPart.Append(UKismetStringLibrary::Conv_IntToString(Score)))));

		PlayerScore->SetText(FText::Format(INVTEXT("Score: {0}"), Score));
	}
}
	

void UPlayerHud::UpdateTime(int32 Time)
{
	if (Time == -1)
	{
		//return UKismetTextLibrary::Conv_StringToText(FString("Wall Spawned!"));
		LastScoreHitTimer->SetText(FText::Format(INVTEXT("Time: {0}"), Time));
	}
	else
	{
	/*	FString FirstPart = "Time: ";
		LastScoreHitTimer->SetText(UKismetTextLibrary::Conv_StringToText((FirstPart.Append(UKismetStringLibrary::Conv_IntToString(Time)))));*/

		LastScoreHitTimer->SetText(FText::Format(INVTEXT("Time: {0}"), Time));
	}
}
