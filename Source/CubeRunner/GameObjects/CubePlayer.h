#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../GameModeAndInterfaces/CubePlayerInterface.h"
#include "CubePlayer.generated.h"

UCLASS()
class CUBERUNNER_API ACubePlayer : public ACharacter, public ICubePlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite)
	float DeltaLocationX;

	UPROPERTY(BlueprintReadWrite)
	float DeltaSeconds;

public:
	void SetDeltaLocationX_Implementation(float x) override;
	float GetDeltaLocationX_Implementation() override;
};
