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
    NewWeaponStaticMesh->SetupAttachment(pNewObject->GetRootComponent());

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
        ObjectContainer.Add(DropOwnedObject(LeftHandObject));

    if (RightHandObject)
        ObjectContainer.Add(DropOwnedObject(RightHandObject));

    return ObjectContainer;
}

void ABaseWarrior::AttackActiveHitBox(bool bIsActive, UBoxComponent* SelectedBoxWeapon)
{
    if (bIsActive)
        SelectedBoxWeapon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    else
        SelectedBoxWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
