#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UOptionMenu;

UCLASS()
class CUBERUNNER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	virtual void NativeConstruct();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* Resume;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* Options;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCustomButton* QuitGameButton;

	UPROPERTY(EditAnywhere, Category = "Class References")
	TSubclassOf<class UOptionMenu> OptionMenuClassRef;	
	
	UPROPERTY(EditAnywhere, Category = "Class References")
	TSubclassOf<class UPauseMenu> PauseMenuClassRef;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnOptionsClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();
};
