#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSaver.generated.h"

UCLASS()
class CUBERUNNER_API UGameSaver : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString PresetSettingSelected;
};
