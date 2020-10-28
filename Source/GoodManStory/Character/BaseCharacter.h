// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnCharacterDeathActionSignature, class ABaseCharacter*, pBaseCharacter);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
    FOnTakeDamageActionSignature, class ABaseCharacter*, pBaseCharacter, float, RealDamageGive, float, RealDamageTake);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
    FOnTakeLifeActionSignature, class ABaseCharacter*, pBaseCharacter, float, RealLifeGive, float, RealLifeTake);

UCLASS()
class GOODMANSTORY_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ABaseCharacter();

    UPROPERTY(BlueprintAssignable)
    FOnCharacterDeathActionSignature OnCharacterDeath;

    UPROPERTY(BlueprintAssignable)
    FOnTakeDamageActionSignature OnCharacterTakeDamage;

    UPROPERTY(BlueprintAssignable)
    FOnTakeLifeActionSignature OnCharacterTakeLife;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float LifeMax = 100.f;

    UPROPERTY(EditAnywhere, Category = Stats)
    float Life = LifeMax;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
    bool bIsDead = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
    bool bIsExpelled = false;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    /**
    * @brief Function to inflict damage to player
    * @param damage 
    * @return 
    */
    UFUNCTION(BlueprintCallable, Category = "Life")
    void TakeDamageCharacter(float dmg) noexcept;

    UFUNCTION(BlueprintCallable, Category = "Kill")
    virtual void Kill();

    UFUNCTION(BlueprintCallable)
    void Launch(const FVector& Direction, float Force, bool bXYOverride = false, bool bZOverride = false);

    UFUNCTION(BlueprintCallable)
    void Expelled(const FVector& Direction, float Force, bool bXYOverride, bool bZOverride);

    /**
    * @brief Function to heal the player
    * @param dammage
    * @return
    */
    UFUNCTION(BlueprintCallable, Category = "Life")
    void TakeLife(float AdditionnalLife) noexcept;

    /**
    * @brief return the life of the player
    * @return 
    */
    UFUNCTION(BlueprintCallable, Category = "Life")
    FORCEINLINE float GetLife() const noexcept { return Life; }


    UFUNCTION(BlueprintCallable, Category = "Life")
    FORCEINLINE float GetLifeRatio() const noexcept { return Life / LifeMax; }

    UFUNCTION(BlueprintCallable, Category = "Life")
    FORCEINLINE bool IsDead() const noexcept { return bIsDead; }
};
