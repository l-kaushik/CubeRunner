// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Floor.generated.h"

class AEnemy;
class ASafeCube;

UCLASS()
class CUBERUNNER_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void InitVariables();

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<float> LanePositions;
	UPROPERTY(BlueprintReadWrite)
	TArray<FTransform> SpawnLocations;
	UPROPERTY(VisibleDefaultsOnly)
	TArray<AEnemy *> AllCubesRef;

	UPROPERTY(EditAnywhere, Category = "Enemy");
	TSubclassOf<class AEnemy> EnemyCubeBlueprintClass;
	UPROPERTY(EditAnywhere, Category = "Enemy");
	TSubclassOf<class AEnemy> SafeCubeBlueprintClass;

protected:
	UFUNCTION(BlueprintCallable)
	void InitEnemySpawnLocations();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void ExtendFloorTrigger(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OutOfBoundTrigger(AActor* OtherActor);

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FTransform GetAttachPoint();
};
