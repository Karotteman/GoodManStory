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
    PrimaryActorTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UDataTable> WaveDataTableObject(TEXT("DataTable'/Game/Assets/LevelDesign/WaveSetting/WaveDataTable.WaveDataTable'"));

    if (WaveDataTableObject.Succeeded())
    {
        WaveDataTable = WaveDataTableObject.Object;
        
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("OK"));
        
        FWaveInfo* Entry = reinterpret_cast<FWaveInfo*>(WaveDataTable->GetRowMap().begin().Value());

        if (Entry && GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,FString::Printf(TEXT("%d"), Entry->Zone));
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("CANT FIND WAVE DATA TABLE")));
        return;
    }
    
    /*
    static ConstructorHelpers::FClassFinder<APawn> PawnBPClass(TEXT("Blueprint'/Game/Blueprint/Character/Enemies/TrashMob/TrashMob.TrashMob'"));
    if (PawnBPClass.Class != NULL)
    {
        TrashMob = PawnBPClass.Class;
    }*/
}

// Called when the game starts or when spawned
void AEnemiesManager::BeginPlay()
{
    Super::BeginPlay();

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
        if (!TrashMob)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
            return;
        }

        GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::FromInt(NumberMinionToSpawn));

        for (int i = 0; i < NumberMinionToSpawn; i++)
        {
            if (!SpawnersContenor[IndexSpawn])
                GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "uninitialized spawner:" + IndexSpawn);

            FVector RandLocation = FVector{FMath::RandPointInCircle(2500.f), 200.0f};
            Manager.Add(GetWorld()->SpawnActor<ABaseEnemy>(TrashMob.Get(),
                                                           SpawnersContenor[IndexSpawn]->GetActorLocation() +
                                                           RandLocation,
                                                           SpawnersContenor[IndexSpawn]->GetActorRotation(),
                                                           SpawnParams));

            FVector RandScale = FVector{0.60, 0.60, 0.60} + FMath::FRandRange(-0.1, 0.1);
            Manager.Last()->SetActorScale3D(RandScale);
            IndexSpawn++;
            if (IndexSpawn > SpawnersContenor.Num() - 1)
                IndexSpawn = 0;

            if (i == NumberMinionToSpawn)
                Spawning = false;
        }
    }
}
