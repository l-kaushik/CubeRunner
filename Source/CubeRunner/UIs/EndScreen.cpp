
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/EditableText.h"

#include "../GameModeAndInterfaces/GameCore.h"
#include "../GameModeAndInterfaces/GameStateInterface.h"
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
}


void UEndScreen::Execute_MenuButton()
{
}


