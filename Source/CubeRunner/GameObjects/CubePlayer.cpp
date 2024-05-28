#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "../UIs/Menus/PauseMenu.h"
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
	DeltaLocationX = 500.f;

	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultInputContext, 0);
		}
	}
}

// Called every frame
void ACubePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;

	AddActorWorldOffset(FVector(DeltaSeconds * DeltaLocationX,0.0f, 0.0f));

}

// Called to bind functionality to input
void ACubePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACubePlayer::Move);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ACubePlayer::Pause);
	}
}

// Interface functions
void ACubePlayer::SetDeltaLocationX_Implementation(float x)
{
	DeltaLocationX = x;
}

float ACubePlayer::GetDeltaLocationX_Implementation()
{
	return DeltaLocationX;
}

void ACubePlayer::Move(const FInputActionValue& Value)
{
	auto MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.0f, Rotation.Yaw, Rotation.Roll));
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void ACubePlayer::Pause(const FInputActionValue& Value)
{
	// Create pause menu widget
	APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(FPC);
	auto PauseMenu = CreateWidget<UPauseMenu>(FPC, PauseMenuRef);
	check(PauseMenu);
	PauseMenu->AddToPlayerScreen();
	PauseMenu->SetKeyboardFocus();
	FPC->SetInputMode(FInputModeUIOnly());
	FPC->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
