// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "BaseWarrior.generated.h"

UCLASS()
class GOODMANSTORY_API ABaseWarrior : public ABaseCharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABaseWarrior();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* RightHandObject;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* BoxWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* LeftHandObject;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* BoxShield;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float Damage = 20.f;

protected:

    UFUNCTION()
    virtual AActor* DropOwnedObject(UStaticMeshComponent* pObjectToDrop);

    UFUNCTION()
    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult);

    UFUNCTION()
    virtual void OnLeftHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult);

    UFUNCTION()
    virtual void OnHandsObjectsBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult);
    
public:

    UFUNCTION(BlueprintCallable)
    virtual TArray<AActor*> DropOwnedObjects();

    UFUNCTION(BlueprintCallable, Category = "Attack")
    float GetDamage() const { return Damage; }

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void SetDamage(float NewDamage) { Damage = NewDamage; }

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void AttackActiveHitBox(bool bIsActive, class UBoxComponent* SelectedBoxWeapon);
};
