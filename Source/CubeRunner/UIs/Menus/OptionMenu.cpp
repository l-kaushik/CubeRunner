#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/EditableText.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "../../GameObjects/GameSaver.h"
#include "OptionMenu.h"

FReply UOptionMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Escape || Key == EKeys::P)
	{
		OnBackButtonClicked();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UOptionMenu::NativeConstruct()
{
	// Initialize Variables
	SaveGameSlotName = "Slot1";

	InitializeUIElements();

	LoadSettings();
}

// event function binding
void UOptionMenu::InitializeUIElements()
{
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

	// ResolutionMode
	if (IncrResolution && DecrResolution)
	{
		IncrResolution->OnClicked.AddDynamic(this, &UOptionMenu::OnIncrResolutionClicked);
		DecrResolution->OnClicked.AddDynamic(this, &UOptionMenu::OnDecrResolutionClicked);
	}

	// Apply Settings
	if (ApplySettings)
	{
		ApplySettings->OnClicked.AddDynamic(this, &UOptionMenu::OnApplySettingsClicked);
	}

	// Preset Settings
	if (PresetSettings)
	{
		PresetSettings->OnSelectionChanged.AddDynamic(this, &UOptionMenu::OnPresetSelectionChanged);
	}

	// Back button
	if (Back)
	{
		Back->OnClicked.AddDynamic(this, &UOptionMenu::OnBackButtonClicked);
	}
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

EWindowMode::Type UOptionMenu::ConvertToEWindowMode(int32 InWindowMode)
{
	switch (InWindowMode)
	{
	case 0:
		return EWindowMode::Fullscreen;
	case 1:
		return EWindowMode::WindowedFullscreen;
	case 2:
		return EWindowMode::Windowed;
	default:
		return EWindowMode::Windowed;
	}
}

int32 UOptionMenu::EWindowModeToInt(EWindowMode::Type InWindowMode)
{
	switch (InWindowMode)
	{
	case EWindowMode::Fullscreen:
		return 0;
	case EWindowMode::WindowedFullscreen:
		return 1;
	case EWindowMode::Windowed:
		return 2;
	default:
		return 2;
	}
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

// Apply Settings
void UOptionMenu::OnApplySettingsClicked()
{
	auto GameSettings = UGameUserSettings::GetGameUserSettings();

	if (GameSettings)
	{
		GameSettings->SetFrameRateLimit(FrameRate);
		GameSettings->SetScreenResolution(Resolution);
		GameSettings->SetShadowQuality(ShadowQuality);
		GameSettings->SetShadingQuality(ShadingQuality);
		GameSettings->SetAntiAliasingQuality(AAQuality);
		GameSettings->SetTextureQuality(TextureQuality);
		GameSettings->SetVSyncEnabled(VSyncEnabled);
		GameSettings->SetFullscreenMode(ConvertToEWindowMode(WindowMode));
		GameSettings->ApplyResolutionSettings(false);
		GameSettings->ApplyNonResolutionSettings();
		GameSettings->ApplySettings(false);
		GameSettings->SaveSettings();
	}
	else
	{
		// raise error
	}
}

// Preset Settings
void UOptionMenu::OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	auto GameSettings =	UGameUserSettings::GetGameUserSettings();

	if (GameSettings)
	{
		SavePresetSetting();
		PresetSettings->SetSelectedOption(SelectedItem);

		if (SelectedItem == "Low")
		{
			GameSettings->SetOverallScalabilityLevel(0);
		}
		else if (SelectedItem == "Medium")
		{
			GameSettings->SetOverallScalabilityLevel(1);
		}
		else if (SelectedItem == "High")
		{
			GameSettings->SetOverallScalabilityLevel(2);
		}
		else if (SelectedItem == "Epic")
		{
			GameSettings->SetOverallScalabilityLevel(3);
		}
		else if (SelectedItem == "Cinematic")
		{
			GameSettings->SetOverallScalabilityLevel(4);;
		}
		else
		{
			GameSettings->SetOverallScalabilityLevel(1);;
		}

		GameSettings->ApplySettings(true);
		GameSettings->SaveSettings();
		LoadSettings();
	}
}

void UOptionMenu::SavePresetSetting()
{
	if (!SaveGame)
	{
		SaveGame =Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
	}
	SaveGame->PresetSettingSelected = PresetSelected;

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveGameSlotName, 0);
}

void UOptionMenu::LoadPresetSetting()
{
	auto LoadGame = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0));

	if (LoadGame)
	{
		PresetSelected = LoadGame->PresetSettingSelected;
	}
}

void UOptionMenu::LoadSettings()
{
	// Fill resolution Array
	FillResolutionArray();
	LoadPresetSetting();
	PresetSettings->SetSelectedOption(PresetSelected);

	auto GameSettings = UGameUserSettings::GetGameUserSettings();

	if (GameSettings)
	{
		//GameSettings->LoadSettings(true);
		FrameRate = GameSettings->GetFrameRateLimit();
		Resolution = GameSettings->GetScreenResolution();
		ShadowQuality = GameSettings->GetShadowQuality();
		ShadingQuality = GameSettings->GetShadingQuality();
		AAQuality = GameSettings->GetAntiAliasingQuality();
		TextureQuality = GameSettings->GetTextureQuality();
		VSyncEnabled = GameSettings->IsVSyncEnabled();
		WindowMode = EWindowModeToInt(GameSettings->GetFullscreenMode());

		// set resolution index
		switch (Resolution.X)
		{
		case 720: ResolutionIndex = 0;
			break;
		case 1280: ResolutionIndex = 1;
			break;
		case 1920: ResolutionIndex = 2;
			break;
		case 2560: ResolutionIndex = 3;
			break;
		default: ResolutionIndex = 1;
			break;
		}
		
		//OnApplySettingsClicked();
	}
}

void UOptionMenu::OnBackButtonClicked()
{
	// Remove other widgets
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

	// create previous widget
	APlayerController * FPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(FPC);
	auto PreviousWidget = CreateWidget(FPC, PreviousWidgetReference);
	check(PreviousWidget);
	PreviousWidget->AddToPlayerScreen();
	PreviousWidget->SetKeyboardFocus();
}
