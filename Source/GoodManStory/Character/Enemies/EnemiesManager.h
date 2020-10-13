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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* WaveDataTable = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABaseEnemy> TrashMob = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ABaseEnemy*> Manager;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ABaseEnemy>> EnemiesStatsContenor;
		
	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnersContenor;

	UPROPERTY(EditAnywhere)
	TArray<UShapeComponent*> ZonesContenor;

	FTimerHandle TimerActuMinionSpawn;

	bool bWaveSpawnerIsRunning = true;

	UPROPERTY(VisibleAnywhere)
	uint16 WaveIndex = 0;
	
	/**
	 * @brief Pointor to the struct of the current wave. If nullptr, there is not wave
	 */
	struct FWaveInfo* pCurrentWave = nullptr;

	UFUNCTION(BlueprintCallable)
    void CheckIfCurrentWaveSpawnerIsEmpty();
    
 	UFUNCTION(BlueprintCallable)
    bool IsAllEnemiesDied();
	
	UFUNCTION(BlueprintCallable)
	void Spawn(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void NextWave();

	UFUNCTION(BlueprintCallable)
	void SendSpawnsRequestsToSpawners();

	FActorSpawnParameters SpawnParams;
	bool Spawning = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
