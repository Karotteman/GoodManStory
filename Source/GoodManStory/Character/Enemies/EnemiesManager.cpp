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
#include "Utility/Utility.h"

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
        DeathEnemyContainer.Reserve(MaxDeathEnemies);
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

    if (bWaveSpawnerIsRunning)
    {
        Spawn(DeltaTime);
    }
    else if ( WaveIndex < WaveDataTable->GetRowMap().Num() && IsAllEnemiesDied())
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
    bool rst = false;
    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num() && !rst; ++i)
    {
         rst |= (pCurrentWave->SpawnInfoContainer[i].EnemyCounter != 0);
    }
    
    bWaveSpawnerIsRunning = rst;
}

bool AEnemiesManager::IsAllEnemiesDied()
{
    return LivingEnemyContainer.Num() == 0;
}

void AEnemiesManager::CheckIfPlayerCanStartTheWave()
{
    if (pCurrentWave == nullptr)
    {
        FWaveInfo* pFirstWave = reinterpret_cast<FWaveInfo*>(WaveDataTable->GetRowMap().begin().Value());
        if (pFirstWave->ZoneID == -1 || ZonesContainer[pFirstWave->ZoneID]->IsPlayerOnThisZone())
            bPlayerCanStartTheWave = true;
    }
    else
    {
        if (pCurrentWave->ZoneID == -1 || ZonesContainer[pCurrentWave->ZoneID]->IsPlayerOnThisZone())
            bPlayerCanStartTheWave = true;
    }
}

void AEnemiesManager::Spawn(float DeltaTime)
{
    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num(); ++i)
    {
        if (pCurrentWave->SpawnInfoContainer[i].EnemyCounter == 0)
            continue;

        pCurrentWave->SpawnInfoContainer[i].TimeCount += DeltaTime;

        if (pCurrentWave->SpawnInfoContainer[i].TimeCount >= pCurrentWave->SpawnInfoContainer[i].SpawnIntervalDelay)
        {
            pCurrentWave->SpawnInfoContainer[i].TimeCount -= pCurrentWave->SpawnInfoContainer[i].SpawnIntervalDelay;

            if (true) //Can spawn with max entity number
            {
                const int IndexSpawner = pCurrentWave->SpawnInfoContainer[i].SpawnerID != -1 ?
                                             pCurrentWave->SpawnInfoContainer[i].SpawnerID :
                                             FMath::RandRange(0, SpawnersContainer.Num() - 1);

                const FVector RandLocation = FVector{
                    FMath::RandPointInCircle(pCurrentWave->SpawnInfoContainer[i].SpawnRadius),
                    0.0f
                };

                if (IndexSpawner >= SpawnersContainer.Num())
                {
                    if (GEngine)
                        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
                                                         TEXT(
                                                             "SpawnerID invalide to spawn entity. Please check the dataTable spawner Id and if spawner is insert on EnemyManager spawner contenor"));
                    return;
                }

                ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(
                    pCurrentWave->SpawnInfoContainer[i].EnemyType.Get(),
                    SpawnersContainer[IndexSpawner]->GetActorLocation() + RandLocation,
                    SpawnersContainer[IndexSpawner]->GetActorRotation(), SpawnParams);

                float Scale;
                if (NewEnemy->bRandomSize)
                    Scale = FMath::RandRange(NewEnemy->GetSizeMin(),NewEnemy->GetSizeMax());
                else
                    Scale = NewEnemy->GetSize();

                FVector RandScale = FVector{Scale,Scale,Scale};            
                NewEnemy->SetActorScale3D(RandScale);
                
                NewEnemy->OnCharacterDeath.AddDynamic(this, &AEnemiesManager::MoveLivingEnemyOnDeathContainer);
                LivingEnemyContainer.Add(NewEnemy);

                pCurrentWave->SpawnInfoContainer[i].EnemyCounter--;

                if (pCurrentWave->SpawnInfoContainer[i].EnemyCounter == 0)
                {
                    CheckIfCurrentWaveSpawnerIsEmpty();
                }
            }
        }
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

    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num(); ++i)
    {
        pCurrentWave->SpawnInfoContainer[i].EnemyCounter = pCurrentWave->SpawnInfoContainer[i].EnemyNumber;
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

    bWaveSpawnerIsRunning  = true;
    bPlayerCanStartTheWave = false;
}

void AEnemiesManager::SendSpawnsRequestsToSpawners()
{
    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num(); ++i)
    {
        //SpawnersContainer[pCurrentWave->SpawnInfoContainer[i].SpawnerID].ReceiveSpawnRequest();
    }
}

void AEnemiesManager::MoveLivingEnemyOnDeathContainer(ABaseCharacter* pCharacter)
{
    LivingEnemyContainer.Remove(Cast<ABaseEnemy>(pCharacter));

    if (DeathEnemyContainer.Num() == MaxDeathEnemies)
    {
        DeathEnemyContainer[0]->Destroy();
        DeathEnemyContainer.RemoveAt(0);
    }

    DeathEnemyContainer.Add(Cast<ABaseEnemy>(pCharacter));   
}
