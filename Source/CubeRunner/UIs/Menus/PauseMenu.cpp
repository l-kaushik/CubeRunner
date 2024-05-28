#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Widget.h"

#include "../Assets/CustomButton.h"
#include "OptionMenu.h"
#include "PauseMenu.h"

FReply UPauseMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Escape || Key == EKeys::P)
	{
		OnResumeClicked();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

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
	UWidget::RemoveFromParent();
	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	auto PlayerController = UGameplayStatics::GetPlayerController(UUserWidget::GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(FInputModeGameOnly());
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
	OptionMenu->SetKeyboardFocus();
}

void UPauseMenu::OnQuitGameButtonClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
