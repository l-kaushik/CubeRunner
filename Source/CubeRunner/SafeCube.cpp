// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameCore.h"
#include "SafeCube.h"

// Called when the game starts or when spawned
void ASafeCube::BeginPlay()
{
	Super::BeginPlay();
}

void ASafeCube::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(),0))) {

		Cast<AGameCore>(UGameplayStatics::GetGameMode(GetWorld()))->SetScore_Implementation(1);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Safe"));
		// play sound at location 

		this->Destroy();
	}
}