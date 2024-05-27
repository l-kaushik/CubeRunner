// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameUserSettings.h"

#include "../UIs/EndScreen.h"
#include "../UIs/Menus/OptionMenu.h"
#include "../LevelScripts/BaseLevelScript.h"

void ABaseLevelScript::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ABaseLevelScript::OnTriggerBoxBeginOverlap);
	}

	LoadGameSettings();
}

void ABaseLevelScript::OnTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// create end screen widget

		APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		check(FPC);
		auto EndScreenWidget= CreateWidget(FPC, EndScreenRef);
		check(EndScreenWidget);
		EndScreenWidget->AddToPlayerScreen();
		EndScreenWidget->SetKeyboardFocus();
	}
}

void ABaseLevelScript::LoadGameSettings()
{	
	if (auto GameSettings = UGameUserSettings::GetGameUserSettings())
	{
		GameSettings->LoadSettings();
	}
}
