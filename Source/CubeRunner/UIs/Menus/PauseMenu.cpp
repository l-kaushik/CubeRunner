#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Widget.h"

#include "../Assets/CustomButton.h"
#include "OptionMenu.h"
#include "PauseMenu.h"

void UPauseMenu::NativeConstruct()
{
	if (Resume)
	{
		Resume->OnButtonClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
	}

	if (Options)
	{
		Options->OnButtonClicked.AddDynamic(this, &UPauseMenu::OnOptionsClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnButtonClicked.AddDynamic(this, &UPauseMenu::OnQuitGameButtonClicked);
	}
}

void UPauseMenu::OnResumeClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	
	auto PlayerController = UGameplayStatics::GetPlayerController(UUserWidget::GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UWidget::RemoveFromParent();
}

void UPauseMenu::OnOptionsClicked()
{
	// Remove this widget
	UWidget::RemoveFromParent();

	// Create option widget
	APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(FPC);
	auto OptionMenu = CreateWidget<UOptionMenu>(FPC, OptionMenuClassRef);
	check(OptionMenu);
	OptionMenu->PreviousWidgetReference = PauseMenuClassRef;
	OptionMenu->AddToPlayerScreen();
}

void UPauseMenu::OnQuitGameButtonClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}