// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "EnemiesManager.generated.h"

UCLASS()
class GOODMANSTORY_API AEnemiesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemiesManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectSpawn")
	class UBlueprint* TrashMob;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager")
	TArray<class ABaseEnemy*> Manager;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawnSettings")
	int NumberMinionToSpawn = 0;
	int NumberMinionToSpawnCurr = 0;
	int IndexSpawn = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawnSettings")
	TArray<AActor*> Spawners;

	FTimerHandle TimerActuMinionSpawn;

	void Spawn();


	FActorSpawnParameters SpawnParams;
	bool Spawning = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
