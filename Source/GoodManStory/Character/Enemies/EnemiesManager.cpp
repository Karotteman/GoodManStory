// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesManager.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "BaseEnemy.h"
#include "Math/UnrealMathUtility.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemiesManager::AEnemiesManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemiesManager::BeginPlay()
{
    Super::BeginPlay();
    //GetWorldTimerManager().SetTimer(TimerActuMinionSpawn, this, &AEnemiesManager::Spawn, 0.5, true, 1.0f);
    if (TrashMob)
    {
        SpawnParams.Owner                          = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    }
}

// Called every frame
void AEnemiesManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEnemiesManager::Spawn()
{
    if (Spawning)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::FromInt(NumberMinionToSpawn));

        for (int i = 0; i < NumberMinionToSpawn; i++)
        {
            if (!Spawners[IndexSpawn])
                GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "uninitialized spawner:" + IndexSpawn);

            FVector RandLocation = FVector{FMath::RandPointInCircle(1000.f), 200.0f};
            Manager.Add(GetWorld()->SpawnActor<ABaseEnemy>(TrashMob->GeneratedClass,
                                                           Spawners[IndexSpawn]->GetActorLocation() + RandLocation,
                                                           Spawners[IndexSpawn]->GetActorRotation(), SpawnParams));
            //NumberMinionToSpawnCurr++;
            IndexSpawn++;
            if (IndexSpawn > Spawners.Num() - 1)
                IndexSpawn = 0;

            if (i == NumberMinionToSpawn)
            {
                Spawning = false;
                //NumberMinionToSpawnCurr = 0;
                //GetWorldTimerManager().ClearTimer(TimerActuMinionSpawn);
            }
        }
    }
}
