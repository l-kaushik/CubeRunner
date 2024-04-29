#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndScreen.generated.h"

UCLASS()
class CUBERUNNER_API UEndScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	int32 Score;

	virtual void NativeConstruct();

	// widget to end screen
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableText* PlayerScored;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	// Button to open main menu
	class UCustomButton* MainMenu;

	UFUNCTION()
	void OnMainMenuClicked();
};
