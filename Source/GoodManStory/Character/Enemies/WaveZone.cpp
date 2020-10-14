// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveZone.h"

#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "NavAreas/NavArea_Null.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1

// Sets default values
AWaveZone::AWaveZone()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    Collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Collider->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);
    //Collider->AreaClass = UNavArea_Null::StaticClass(); //Dont work because in private but in edit anywhere...
}

void AWaveZone::BeginPlay() { }

bool AWaveZone::IsPlayerOnThisZone()
{
    return Collider->IsOverlappingActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
