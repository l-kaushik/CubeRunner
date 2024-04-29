
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/EditableText.h"

#include "../GameModeAndInterfaces/GameCore.h"
#include "../GameModeAndInterfaces/GameStateInterface.h"
#include "Assets/CustomButton.h"
#include "EndScreen.h"

void UEndScreen::NativeConstruct()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode && GameMode->Implements<UGameStateInterface>())
	{
		Score = IGameStateInterface::Execute_GetCurrentScore(GameMode);

		// Update Score UI
		if (PlayerScored)
		{
			PlayerScored->SetText(FText::Format(INVTEXT("You Scored: {0}"), Score));
		}

		// Set Input Mode and Mouse Cursor

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	}

	// Setting up main menu button
	if (MainMenu)
	{
		MainMenu->OnButtonClicked.AddDynamic(this, &UEndScreen::OnMainMenuClicked);
	}
}

void UEndScreen::OnMainMenuClicked()
{
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Blue, FString("Main Menu Clicked"));
}


