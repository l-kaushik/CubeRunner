#include "CubePlayer.h"

// Sets default values
ACubePlayer::ACubePlayer()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACubePlayer::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACubePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACubePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACubePlayer::SetDeltaLocationX_Implementation()
{

}

float ACubePlayer::GetDeltaLocationX_Implementation()
{
	return DeltaLocationX;
}
