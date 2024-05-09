#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/EditableText.h"
#include "OptionMenu.h"

void UOptionMenu::NativeConstruct()
{
	// event function binding

	// Frame Rate
	if (IncrFPS && DecrFPS)
	{
		IncrFPS->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrFPSClicked);
		DecrFPS->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrFPSClicked);
	}

	// Anti-Aliasing
	if (IncrAliasing && DecrAliasing)
	{
		IncrAliasing->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrAAClicked);
		DecrAliasing->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrAAClicked);
	}

	// VSync
	if (IncrVSync && DecrVSync)
	{
		IncrVSync->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrVSyncClicked);
		DecrVSync->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrVSyncClicked);
	}
}

void UOptionMenu::OnPresetSettingClicked()
{
}

// Frame Rate

void UOptionMenu::OnIncrFPSClicked()
{
	FrameRate = UKismetMathLibrary::FClamp(FrameRate + 30.f, 30.f, 180.f);
}

void UOptionMenu::OnDecrFPSClicked()
{
	FrameRate = UKismetMathLibrary::FClamp(FrameRate - 30.f, 30.f, 180.f);
}

// Anti-Aliasing

void UOptionMenu::OnIncrAAClicked()
{
	AAQuality = UKismetMathLibrary::Clamp(AAQuality + 1, 0, 4);
}

void UOptionMenu::OnDecrAAClicked()
{
	AAQuality = UKismetMathLibrary::Clamp(AAQuality - 1, 0, 4);
}

// VSync

void UOptionMenu::OnIncrVSyncClicked()
{
	VSyncEnabled = true;
}

void UOptionMenu::OnDecrVSyncClicked()
{
	VSyncEnabled = false;
}
