// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "../GameModeAndInterfaces/GameCore.h"
#include "SafeCube.h"

// Called when the game starts or when spawned
void ASafeCube::BeginPlay()
{
	Super::BeginPlay();
}

void ASafeCube::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(),0))) {

		auto GameMode = GetWorld()->GetAuthGameMode();
		if (GameMode->Implements<UGameStateInterface>())
		{
			IGameStateInterface::Execute_SetScore(GameMode, 1);

		}

		// play sound at location 

		this->Destroy();
	}
}
