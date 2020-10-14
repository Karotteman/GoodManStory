// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesManager.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "BaseEnemy.h"
#include "GoodManStory/Wave/WaveInfo.h"
#include "Math/UnrealMathUtility.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEnemiesManager::AEnemiesManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UDataTable> WaveDataTableObject(
        TEXT("DataTable'/Game/Assets/LevelDesign/WaveSetting/WaveDataTable.WaveDataTable'"));

    if (WaveDataTableObject.Succeeded())
    {
        WaveDataTable = WaveDataTableObject.Object;

        pCurrentWave = reinterpret_cast<FWaveInfo*>(WaveDataTable->GetRowMap().begin().Value());

        for (int i = 0; i < pCurrentWave->SpawnInfoContenor.Num(); ++i)
        {
           pCurrentWave->SpawnInfoContenor[i].EnemyCounter = pCurrentWave->SpawnInfoContenor[i].EnemyNumber;
        }
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("CANT FIND WAVE DATA TABLE")));
        return;
    }
}

// Called when the game starts or when spawned
void AEnemiesManager::BeginPlay()
{
    Super::BeginPlay();

    if (TrashMob)
    {
        SpawnParams.Owner                          = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    }
}

// Called every frame
void AEnemiesManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
   
    if (bWaveSpawnerIsRunning && IsAllEnemiesDied())
    {
        Spawn(DeltaTime);
    }
    else
    {
        if (bPlayerCanStartTheWave)
        {
            NextWave();
        }
        else
        {
            CheckIfPlayerCanStartTheWave();
        }
    }
}

void AEnemiesManager::CheckIfCurrentWaveSpawnerIsEmpty()
{
    for (int i = 0; i < pCurrentWave->SpawnInfoContenor.Num() && bWaveSpawnerIsRunning; ++i)
    {
        bWaveSpawnerIsRunning &= (pCurrentWave->SpawnInfoContenor[i].EnemyCounter == 0);
    }
}

bool AEnemiesManager::IsAllEnemiesDied()
{
    TArray<AActor*> children;
    GetAttachedActors(children);
    return children.Num() == 0;
}

void AEnemiesManager::CheckIfPlayerCanStartTheWave()
{
    if (pCurrentWave->ZoneID == -1 || ZonesContenor[pCurrentWave->ZoneID]->IsPlayerOnThisZone())
        bPlayerCanStartTheWave = true;
}

void AEnemiesManager::Spawn(float DeltaTime)
{    
    for (int i = 0; i < pCurrentWave->SpawnInfoContenor.Num(); ++i)
    {
        if (pCurrentWave->SpawnInfoContenor[i].EnemyCounter == 0)
            continue;

        pCurrentWave->SpawnInfoContenor[i].TimeCount += DeltaTime;

        if (pCurrentWave->SpawnInfoContenor[i].TimeCount >= pCurrentWave->SpawnInfoContenor[i].SpawnIntervalDelay)
        {
            pCurrentWave->SpawnInfoContenor[i].TimeCount -= pCurrentWave->SpawnInfoContenor[i].SpawnIntervalDelay;

            if (true) //Can spawn with max entity number
            {
                const int IndexSpawner = pCurrentWave->SpawnInfoContenor[i].SpawnerID != -1 ? 
                pCurrentWave->SpawnInfoContenor[i].SpawnerID : FMath::RandRange(0, SpawnersContenor.Num() - 1);

                const FVector RandLocation = FVector{
                    FMath::RandPointInCircle(pCurrentWave->SpawnInfoContenor[i].SpawnRadius),
                    200.0f
                };

                if (IndexSpawner >= SpawnersContenor.Num())
                {
                    if (GEngine)
                        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
                                                         TEXT(
                                                             "SpawnerID invalide to spawn entity. Please check the dataTable spawner Id and if spawner is insert on EnemyManager spawner contenor"));
                    return;
                }
                
                Manager.Add(GetWorld()->SpawnActor<ABaseEnemy>(pCurrentWave->SpawnInfoContenor[i].EnemyType.Get(),
                                                               SpawnersContenor[IndexSpawner]->GetActorLocation() +
                                                               RandLocation,
                                                               SpawnersContenor[IndexSpawner]->GetActorRotation(),
                                                               SpawnParams));

                pCurrentWave->SpawnInfoContenor[i].EnemyCounter--;

                if (pCurrentWave->SpawnInfoContenor[i].EnemyCounter == 0)
                {
                    CheckIfCurrentWaveSpawnerIsEmpty();
                }
                
            }
        }
        //SpawnersContenor[pCurrentWave->SpawnInfoContenor[i].SpawnerID].ReceiveSpawnRequest();
    }
}

void AEnemiesManager::NextWave()
{
    /*Pass to the next wave*/
    TMap<FName, unsigned char*>::TRangedForConstIterator WaveTableIterator = WaveDataTable->GetRowMap().begin();

    for (int i = 0; i < WaveIndex; ++i)
    {
        ++WaveTableIterator;
    }
    WaveIndex++; //Increment for the next wave
    
    pCurrentWave = reinterpret_cast<FWaveInfo*>(WaveTableIterator.Value());

    for (int i = 0; i < pCurrentWave->SpawnInfoContenor.Num(); ++i)
    {
        pCurrentWave->SpawnInfoContenor[i].EnemyCounter = pCurrentWave->SpawnInfoContenor[i].EnemyNumber;
    }

    if (!pCurrentWave)
    {
        pCurrentWave = nullptr;

        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Cannot found next wave"));

        return;
    }

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Next wave"));

    bWaveSpawnerIsRunning = true;
    bPlayerCanStartTheWave = false;
}

void AEnemiesManager::SendSpawnsRequestsToSpawners()
{
    for (int i = 0; i < pCurrentWave->SpawnInfoContenor.Num(); ++i)
    {
        //SpawnersContenor[pCurrentWave->SpawnInfoContenor[i].SpawnerID].ReceiveSpawnRequest();
    }
}
