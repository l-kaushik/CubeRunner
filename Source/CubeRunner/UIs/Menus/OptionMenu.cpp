#include "OptionMenu.h"

// Sets default values
AOptionMenu::AOptionMenu()
{
	// Set this empty to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOptionMenu::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOptionMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AOptionMenu::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
