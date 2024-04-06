// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DeathWall.h"

// Sets default values
ADeathWall::ADeathWall()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADeathWall::OnBoxBeginOverlap);

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CubeMesh"));
	WallMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ADeathWall::BeginPlay()
{
	Super::BeginPlay();
}

void ADeathWall::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {
		OtherActor->AddActorWorldOffset(FVector(0.0f, 0.0f, 0.0f));

		UE_LOG(LogTemp, Warning,TEXT("Cube is being overlapped"))

			//Create End UI
	}
}

