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

	// remove BlueprintReadWrite later
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* PresetSetting;

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

	UFUNCTION()
	void OnPresetSettingClicked();
	UFUNCTION()
	void OnIncrFPSClicked();
	UFUNCTION()
	void OnDecrFPSClicked();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrameRate;

};
