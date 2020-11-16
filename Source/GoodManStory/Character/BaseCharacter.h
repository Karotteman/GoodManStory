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

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterSpawnActionSignature);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterIsDestroyActionSignature);

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

    UPROPERTY(BlueprintAssignable)
    FOnCharacterSpawnActionSignature OnCharacterSpawn;

    UPROPERTY(BlueprintAssignable)
    FOnCharacterIsDestroyActionSignature OnCharacterIsDestroy;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Destroyed() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float LifeMax = 100.f;

    UPROPERTY(EditAnywhere, Category = Stats)
    float Life = LifeMax;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
    bool bIsDead = false;

private :

    /**
     * @brief Use virtual getter and setter
     */
    UPROPERTY()
    bool bIsStun = false;
    
protected :

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    bool bIsStunable = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float StunRecoveryDelay = 3.f;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

public :
    
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
    void LaunchAndStun(const FVector& Force, bool bXYOverride, bool bZOverride);

    UFUNCTION(BlueprintCallable)
    void SetMaxLifeAndAddLifeDiff(float NewMaxLife);
    
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

    UFUNCTION(BlueprintCallable)
    virtual void SetIsStun(bool bNewStun) noexcept { bIsStun = bNewStun; }

    UFUNCTION(BlueprintCallable)
    void SetIsStunable(bool bNewIsStunable) noexcept { bIsStunable = bNewIsStunable; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsStunable() const noexcept { return bIsStunable; }
    
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsStun() const noexcept { return bIsStun; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE float GetStunRecoveryDelay() const { return StunRecoveryDelay; }

    UFUNCTION(BlueprintCallable)
    void SetStunRecoveryDelay(float NewStunRecoveryDelay) { StunRecoveryDelay = NewStunRecoveryDelay; }

    UFUNCTION(BlueprintCallable)
    void StartStunRecovery() noexcept;
};
