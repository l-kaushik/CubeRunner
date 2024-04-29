#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"
#include "CustomButton.h"

UCustomButton::UCustomButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TextColor = FLinearColor::Black;
	BackgroundColor = FLinearColor::White;
}

void UCustomButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CustomButton)
	{
		CustomButton->SetColorAndOpacity(TextColor);
		CustomButton->SetBackgroundColor(BackgroundColor);
	}

	if (ButtonText)
	{
		ButtonText->SetText(Text);
		ButtonText->SetFont(Font);
		ButtonText->SetRenderTransform(Transform);
	}

	if (CustomButton)
	{
		// Setting up Event
		CustomButton->OnClicked.AddDynamic(this, &UCustomButton::InternalOnButtonClicked);
	}
}

void UCustomButton::ClickButton()
{
	InternalOnButtonClicked();
}

void UCustomButton::InternalOnButtonClicked()
{
	OnButtonClicked.Broadcast();
}