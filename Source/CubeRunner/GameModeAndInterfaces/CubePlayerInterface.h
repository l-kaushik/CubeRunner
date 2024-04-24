#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CubePlayerInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCubePlayerInterface : public UInterface
{
	GENERATED_BODY()
};

// Actual Interface Class
class ICubePlayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetDeltaLocationX(float x);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetDeltaLocationX();

};