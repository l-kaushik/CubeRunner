#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "../Assets/CustomButton.h"
#include "MainMenu.h"

void UMainMenu::NativeConstruct()
{
	if (Play)
	{
		Play->OnButtonClicked.AddDynamic(this, &UMainMenu::OnPlayClicked);
	}	
	
	if (Options)
	{
		Options->OnButtonClicked.AddDynamic(this, &UMainMenu::OnOptionsClicked);
	}	
	
	if (QuitGameButton)
	{
		QuitGameButton->OnButtonClicked.AddDynamic(this, &UMainMenu::OnQuitGameButtonClicked);
	}
}

void UMainMenu::OnPlayClicked()
{
	// open base level
	UGameplayStatics::OpenLevel(GetWorld(), "Base");
}

void UMainMenu::OnOptionsClicked()
{
	// Remove other widgets
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	// Create option widget
}

void UMainMenu::OnQuitGameButtonClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
