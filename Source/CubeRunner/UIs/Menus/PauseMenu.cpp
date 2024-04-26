#include "PauseMenu.h"

// Sets default values
APauseMenu::APauseMenu()
{
	// Set this empty to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APauseMenu::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APauseMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APauseMenu::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
