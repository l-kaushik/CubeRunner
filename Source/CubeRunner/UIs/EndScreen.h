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


public:

	virtual void NativeConstruct();

	void Execute_MenuButton();

	// widget to end screen
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableText* PlayerScored;

};
