// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/World.h"
#include "EnemiesManager.generated.h"

class UDataTable;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inspector")
	class UDataTable* WaveDataTable = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inspector")
	TSubclassOf<class ABaseEnemy> TrashMob = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inspector")
	TArray<class ABaseEnemy*> Manager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inspector")
	int NumberMinionToSpawn = 0;
	
	int NumberMinionToSpawnCurr = 0;
	int IndexSpawn = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inspector")
	TArray<AActor*> SpawnersContenor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inspector")
	TArray<UShapeComponent*> ZonesContenor;

	FTimerHandle TimerActuMinionSpawn;

	UFUNCTION(BlueprintCallable, Category= "Spawn")
	void Spawn();

	FActorSpawnParameters SpawnParams;
	bool Spawning = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
