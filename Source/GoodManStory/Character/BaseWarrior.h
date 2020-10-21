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
	
protected:

    UPROPERTY(EditAnywhere, Category = Stats)
    float Damage = 20.f;

public:
    
    UFUNCTION(BlueprintCallable, Category = "Attack")
    void AttackActiveHitBox(bool bIsActive, class UBoxComponent* BoxWeapon);
};
