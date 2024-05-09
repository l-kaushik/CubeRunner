#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/EditableText.h"
#include "OptionMenu.h"

void UOptionMenu::NativeConstruct()
{
	// Fill resolution Array
	FillResolutionArray();

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

	// Shader
	if (IncrShader && DecrShader)
	{
		IncrShader->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrShaderClicked);
		DecrShader->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrShaderClicked);
	}

	// Shadow
	if (IncrShadow && DecrShadow)
	{
		IncrShadow->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrShadowClicked);
		DecrShadow->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrShadowClicked);
	}

	// Textue
	if (IncrTexture && DecrTexture)
	{
		IncrTexture->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrTextureClicked);
		DecrTexture->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrTextureClicked);
	}

	// Window Mode
	if (IncrWindow && DecrWindow)
	{
		IncrWindow->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrWindowClicked);
		DecrWindow->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrWindowClicked);
	}

	//ResolutionMode
	if (IncrResolution && DecrResolution)
	{
		IncrResolution->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrResolutionClicked);
		DecrResolution->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrResolutionClicked);
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

// Shader Quality
void UOptionMenu::OnIncrShaderClicked()
{
	ShadingQuality = UKismetMathLibrary::Clamp(ShadingQuality + 1, 0, 4);
}

void UOptionMenu::OnDecrShaderClicked()
{
	ShadingQuality = UKismetMathLibrary::Clamp(ShadingQuality + 1, 0, 4);
}

// Shadow Quality
void UOptionMenu::OnIncrShadowClicked()
{
	ShadowQuality = UKismetMathLibrary::Clamp(ShadowQuality + 1, 0, 4);
}

void UOptionMenu::OnDecrShadowClicked()
{
	ShadowQuality = UKismetMathLibrary::Clamp(ShadowQuality - 1, 0, 4);
}

// Texture Quality
void UOptionMenu::OnIncrTextureClicked()
{
	TextureQuality = UKismetMathLibrary::Clamp(TextureQuality + 1, 0, 4);
}

void UOptionMenu::OnDecrTextureClicked()
{
	TextureQuality = UKismetMathLibrary::Clamp(TextureQuality - 1, 0, 4);
}

// Window Mode
void UOptionMenu::OnIncrWindowClicked()
{
	WindowMode = UKismetMathLibrary::Clamp(WindowMode + 1, 0, 2);
}

void UOptionMenu::OnDecrWindowClicked()
{
	WindowMode = UKismetMathLibrary::Clamp(WindowMode - 1, 0, 2);
}

// Resolution Mode
void UOptionMenu::OnIncrResolutionClicked()
{
	ResolutionIndex = UKismetMathLibrary::Clamp(ResolutionIndex + 1, 0, SupportedResolutions.Num() - 1);
	Resolution = SupportedResolutions[ResolutionIndex];

	for (const auto i : SupportedResolutions)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("x: %d, y: %d"), i.X, i.Y));
	}
}

void UOptionMenu::OnDecrResolutionClicked()
{
	ResolutionIndex = UKismetMathLibrary::Clamp(ResolutionIndex - 1, 0, SupportedResolutions.Num() - 1);
	Resolution = SupportedResolutions[ResolutionIndex];
}

void UOptionMenu::FillResolutionArray()
{
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
}
