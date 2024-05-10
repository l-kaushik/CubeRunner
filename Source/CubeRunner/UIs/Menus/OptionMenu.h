#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionMenu.generated.h"

UCLASS()
class CUBERUNNER_API UOptionMenu : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct();
	void InitializeUIElements();

	// remove BlueprintReadWrite later
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PresetSettings;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrAliasing;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrAliasing;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrFPS;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrFPS;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrResolution;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrResolution;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrShader;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrShader;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrShadow;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrShadow;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrTexture;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrTexture;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrWindow;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrWindow;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncrVSync;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* DecrVSync;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Back;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ApplySettings;

protected:

	// Frame Rate
	UFUNCTION()
	void OnIncrFPSClicked();
	UFUNCTION()
	void OnDecrFPSClicked();	

	// Anti-Aliasing
	UFUNCTION()
	void OnIncrAAClicked();
	UFUNCTION()
	void OnDecrAAClicked();

	// VSync
	UFUNCTION()
	void OnIncrVSyncClicked();
	UFUNCTION()
	void OnDecrVSyncClicked();

	// Shader Quality
	UFUNCTION()
	void OnIncrShaderClicked();
	UFUNCTION()
	void OnDecrShaderClicked();

	// Shadow Quality
	UFUNCTION()
	void OnIncrShadowClicked();
	UFUNCTION()
	void OnDecrShadowClicked();
	
	// Texture Quality
	UFUNCTION()
	void OnIncrTextureClicked();
	UFUNCTION()
	void OnDecrTextureClicked();

	// Window Mode
	UFUNCTION()
	void OnIncrWindowClicked();
	UFUNCTION()
	void OnDecrWindowClicked();
	UFUNCTION()
	EWindowMode::Type ConvertToEWindowMode(int32 WindowMode);
	UFUNCTION()
	int32 EWindowModeToInt(EWindowMode::Type WindowMode);

	// Resolution Mode
	UFUNCTION()
	void OnIncrResolutionClicked();
	UFUNCTION()
	void OnDecrResolutionClicked();
	UFUNCTION(BlueprintCallable)
	void FillResolutionArray();

	// Apply Settings
	UFUNCTION()
	void OnApplySettingsClicked();

	// Preset Settings
	UFUNCTION()
	void OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void SavePresetSetting();

	UFUNCTION()
	void LoadPresetSetting();

	UFUNCTION(BlueprintCallable)
	void LoadSettings();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrameRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AAQuality;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShadingQuality;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShadowQuality;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TextureQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool VSyncEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WindowMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntPoint> SupportedResolutions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResolutionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PresetSelected;

	UPROPERTY()
	UGameSaver* SaveGame;

	UPROPERTY()
	FString SaveGameSlotName;
};
