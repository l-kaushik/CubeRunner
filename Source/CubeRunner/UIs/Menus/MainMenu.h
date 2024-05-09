#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class CUBERUNNER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* Play;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* Options;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* QuitGameButton;
	
	UPROPERTY(EditAnywhere, Category ="Class References")
	TSubclassOf<class UOptionMenu> OptionMenuClass;

	UPROPERTY()
	class UOptionMenu* OptionMenu;

protected:
	UFUNCTION()
	void OnPlayClicked();
	
	UFUNCTION()
	void OnOptionsClicked();
	
	UFUNCTION()
	void OnQuitGameButtonClicked();
};
