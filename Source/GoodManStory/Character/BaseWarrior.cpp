// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWarrior.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ABaseWarrior::ABaseWarrior()
{
    
}

AActor* ABaseWarrior::DropOwnedObject(UStaticMeshComponent* pObjectToDrop)
{
    FTransform WeaponTransform = pObjectToDrop->GetSocketTransform(NAME_None);

    AActor* pNewObject = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), WeaponTransform);

    if (UNLIKELY(!IsValid(pNewObject)))
    {
        UE_LOG(LogTemp, Warning, TEXT("Crash avoided with unvalid Uobject in function DropOwnedObject"));
        return nullptr;
    }
    
    UStaticMeshComponent* NewWeaponStaticMesh = NewObject<UStaticMeshComponent>(this, TEXT("ObjectStaticMesh"));
    NewWeaponStaticMesh->CreationMethod       = EComponentCreationMethod::Native;
    NewWeaponStaticMesh->AttachToComponent(pNewObject->GetRootComponent(),
                                           FAttachmentTransformRules::KeepRelativeTransform);
    NewWeaponStaticMesh->RegisterComponent();

    NewWeaponStaticMesh->SetWorldTransform(WeaponTransform);
    NewWeaponStaticMesh->SetStaticMesh(pObjectToDrop->GetStaticMesh());
    NewWeaponStaticMesh->SetSimulatePhysics((true));
    NewWeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    NewWeaponStaticMesh->ComponentVelocity = pObjectToDrop->GetComponentVelocity();

    pObjectToDrop->DestroyComponent();

    return pNewObject;
}

void ABaseWarrior::OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

void ABaseWarrior::OnLeftHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

void ABaseWarrior::OnHandsObjectsBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

TArray<AActor*> ABaseWarrior::DropOwnedObjects()
{
    TArray<AActor*> ObjectContainer;

    if (LeftHandObject)
    {
        AActor* pObject = DropOwnedObject(LeftHandObject);
        if (LIKELY(IsValid(pObject)))
        {
            ObjectContainer.Add(pObject);
        }
    }
    
    if (RightHandObject)
    {
        AActor* pObject = DropOwnedObject(RightHandObject);
        if (LIKELY(IsValid(pObject)))
        {
            ObjectContainer.Add(pObject);
        }
    }
    
    return ObjectContainer;
}

void ABaseWarrior::AttackActiveHitBox(bool bIsActive, UBoxComponent* SelectedBoxWeapon)
{
    if (UNLIKELY(!IsValid(SelectedBoxWeapon)))
    {
        UE_LOG(LogTemp, Warning, TEXT("Crash avoided with unvalid Uobject in function AttackActiveHitBox of ABaseWarrior"));
        return;
    }
    
    if (bIsActive)
        SelectedBoxWeapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    else
        SelectedBoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
