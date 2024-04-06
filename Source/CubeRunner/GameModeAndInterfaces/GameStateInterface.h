#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

// Actual Interface Class
class IGameStateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetScore(int Score);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CallExtendFloor();
	
};
