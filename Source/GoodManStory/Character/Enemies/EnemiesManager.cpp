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

        /*Reserve emplacement for death enemies*/
        DeathEnemyContainer.Reserve(MaxDeathEnemies);
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("CANT FIND WAVE DATA TABLE")));
        return;
    }

    /*Reserve emplacement for living enemies*/
    for (FEnemyState& EnemyStats : EnemiesStatsContainer)
    {
        EnemyStats.LivingEnemyContainer.Reserve(EnemyStats.MaxNumberOnScene);
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
    else if (WaveIndex < WaveDataTable->GetRowMap().Num() && IsAllEnemiesDied())
    {
        if (bPlayerCanStartTheWave)
        {
            NextWave();
        }
        else
        {
            CheckIfPlayerCanStartTheNextWave();
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

bool AEnemiesManager::IsAllEnemiesDied() const
{
    bool bRst = true;

    for (int i = 0; i < EnemiesStatsContainer.Num() && bRst; ++i)
    {
        bRst &= EnemiesStatsContainer[i].LivingEnemyContainer.Num() == 0;
    }

    return bRst;
}

void AEnemiesManager::CheckIfPlayerCanStartTheNextWave()
{
    TMap<FName, unsigned char*>::TRangedForConstIterator WaveTableIterator = WaveDataTable->GetRowMap().begin();

    for (int i = 0; i < WaveIndex; ++i)
    {
        ++WaveTableIterator;
    }

    FWaveInfo* pNextWave = reinterpret_cast<FWaveInfo*>(WaveTableIterator.Value());
    
    if (pNextWave->ZoneID == -1 || ZonesContainer[pNextWave->ZoneID]->IsPlayerOnThisZone())
        bPlayerCanStartTheWave = true;
}

void AEnemiesManager::Spawn(float DeltaTime)
{
    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num(); ++i)
    {
        /*Info : Block the counter if spaner can't spawn the entity*/
        if (pCurrentWave->SpawnInfoContainer[i].EnemyCounter == 0 || !CanSpawnTheEntityWithoutExcesMaxNumber(
            pCurrentWave->SpawnInfoContainer[i].EnemyType.Get()))
            continue;

        pCurrentWave->SpawnInfoContainer[i].TimeCount += DeltaTime;

        if (pCurrentWave->SpawnInfoContainer[i].bWaitOffset)
        {
            /*Increment offset*/
            if (pCurrentWave->SpawnInfoContainer[i].TimeCount >= pCurrentWave->SpawnInfoContainer[i].
                FirstSpawnDelayOffset)
            {
                /*Is ready to spawn entity*/
                pCurrentWave->SpawnInfoContainer[i].bWaitOffset = false;
                pCurrentWave->SpawnInfoContainer[i].TimeCount -= pCurrentWave->SpawnInfoContainer[i].
                    FirstSpawnDelayOffset;
            }
            else
            {
                /*Is not ready to spawn entity*/
                continue;
            }
        }

        /*Increment spawn interval*/
        if (pCurrentWave->SpawnInfoContainer[i].TimeCount < pCurrentWave->SpawnInfoContainer[i].SpawnIntervalDelay)
            continue;
        else
            pCurrentWave->SpawnInfoContainer[i].TimeCount -= pCurrentWave->SpawnInfoContainer[i].SpawnIntervalDelay;

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

        ABaseEnemy* NewEnemy = GetWorld()->SpawnActor<ABaseEnemy>(pCurrentWave->SpawnInfoContainer[i].EnemyType.Get(),
                                                                  SpawnersContainer[IndexSpawner]->GetActorLocation() +
                                                                  RandLocation,
                                                                  SpawnersContainer[IndexSpawner]->GetActorRotation(),
                                                                  SpawnParams);

        float Scale;
        if (NewEnemy->bRandomSize)
            Scale = FMath::RandRange(NewEnemy->GetSizeMin(), NewEnemy->GetSizeMax());
        else
            Scale = NewEnemy->GetSize();

        FVector RandScale = FVector{Scale, Scale, Scale};
        NewEnemy->SetActorScale3D(RandScale);

        NewEnemy->OnCharacterDeath.AddDynamic(this, &AEnemiesManager::MoveLivingEnemyOnDeathContainer);

        for (FEnemyState& EnemyStats : EnemiesStatsContainer)
        {
            if (pCurrentWave->SpawnInfoContainer[i].EnemyType == EnemyStats.Type)
            {
                EnemyStats.LivingEnemyContainer.Add(NewEnemy);
            }
        }

        pCurrentWave->SpawnInfoContainer[i].EnemyCounter--;

        if (pCurrentWave->SpawnInfoContainer[i].EnemyCounter == 0)
        {
            CheckIfCurrentWaveSpawnerIsEmpty();
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

    /*Init the wave*/
    for (int i = 0; i < pCurrentWave->SpawnInfoContainer.Num(); ++i)
    {
        pCurrentWave->SpawnInfoContainer[i].EnemyCounter = pCurrentWave->SpawnInfoContainer[i].EnemyNumber;
        pCurrentWave->SpawnInfoContainer[i].bWaitOffset  = pCurrentWave->SpawnInfoContainer[i].FirstSpawnDelayOffset >
            0.f;
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

bool AEnemiesManager::CanSpawnTheEntityWithoutExcesMaxNumber(const TSubclassOf<class ABaseEnemy>& Type) const
{
    for (const FEnemyState& EnemyStats : EnemiesStatsContainer)
    {
        if (Type == EnemyStats.Type)
        {
            return EnemyStats.LivingEnemyContainer.Num() != EnemyStats.MaxNumberOnScene;
        }
    }

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
                                         TEXT("TRY TO SPAWN ENEMY NOT REGISTER IN ENEMIES MANAGER"));

    return false;
}

void AEnemiesManager::MoveLivingEnemyOnDeathContainer(ABaseCharacter* pCharacter)
{
    for (FEnemyState& EnemyStats : EnemiesStatsContainer)
    {
        if (pCharacter->GetClass() == EnemyStats.Type.Get())
        {
            EnemyStats.LivingEnemyContainer.Remove(Cast<ABaseEnemy>(pCharacter));
            if (DeathEnemyContainer.Num() == MaxDeathEnemies)
            {
                DeathEnemyContainer[0]->Destroy();
                DeathEnemyContainer.RemoveAt(0);
            }

            DeathEnemyContainer.Add(Cast<ABaseEnemy>(pCharacter));
            return;
        }
    }

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
                                         TEXT("TRY TO REMOVE ENEMY NOT REGISTER IN ENEMIES MANAGER"));
}
