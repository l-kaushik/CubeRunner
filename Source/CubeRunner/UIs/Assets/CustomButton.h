#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomButton.generated.h"

class FText;
struct FSlateColor;
struct FSlateFontInfo;
struct FWidgetTransform;
struct FLinearColor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedSignature);

UCLASS()
class CUBERUNNER_API UCustomButton : public UUserWidget
{
	GENERATED_BODY()
	UCustomButton(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct();

public:

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonClickedSignature OnButtonClicked;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void ClickButton();

protected:
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CustomButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	// CustomButton Attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonText")
	FLinearColor TextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonText")
	FLinearColor BackgroundColor;

	// ButtonText Attribute

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonText")
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonText")
	FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ButtonText")
	FWidgetTransform Transform;

	UFUNCTION()
	void InternalOnButtonClicked();
};
