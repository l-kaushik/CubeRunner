#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/EditableText.h"
#include "OptionMenu.h"

void UOptionMenu::NativeConstruct()
{
	// event function binding

	if (IncrFPS && DecrFPS)
	{
		IncrFPS->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrFPSClicked);
		DecrFPS->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrFPSClicked);
	}
}

void UOptionMenu::OnPresetSettingClicked()
{
}

void UOptionMenu::OnIncrFPSClicked()
{
	FrameRate = UKismetMathLibrary::FClamp(FrameRate + 30.f, 30.f, 180.f);
}

void UOptionMenu::OnDecrFPSClicked()
{
	FrameRate = UKismetMathLibrary::FClamp(FrameRate - 30.f, 30.f, 180.f);
}