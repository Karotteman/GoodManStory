// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoodManStory/Character/BaseWarrior.h"
#include "PhysicsEngine/RadialForceComponent.h"

#include "BasePlayer.generated.h"

class AActor;

/*Stats events*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpActionSignature, int, CurrentLevel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerTakeRageActionSignature, float, CurrrentRage, float, RageTake,
                                               float, RealRageTake);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerTakeScoreActionSignature, float, CurrentScore, float, ScoreTake);

/*Attack events*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerBeginBasicAttackActionSignature, int, IndexCurrentCombo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerBasicAttackHitActionSignature, AActor*, OtherHit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndBasicAttackActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerBeginChargeActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerChargeHitActionSignature, AActor*, OtherHit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndChargeActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerBeginTourbilolActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerTourbilolHitActionSignature, AActor*, OtherHit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndTourbilolActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerBeginEvilCapacityActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndEvilCapacityActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerBeginSwitchCameraActionSignature);

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABasePlayer : public ABaseWarrior
{
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    class UCharacterCameraBoom* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    class UCameraComponent* FollowCamera;

    class UMaterialInstanceDynamic* DynMaterial;

protected:

    UPROPERTY(EditAnywhere, Category = Attack)
    TArray<UAnimMontage*> SlotAnimationsAttackCombo;

    UPROPERTY(EditAnywhere, Category = Attack)
    UAnimMontage* SlotAnimationsCharge;

    UPROPERTY(EditAnywhere, Category = Attack)
    UAnimMontage* SlotAnimationsTourbillol;

    uint8 BasicAttackComboCount = 0;

    class UMonoHitBehaviours* MonoHitBehavioursComponent;

    /**
    * @brief This collider is use when player use its feature "Charge"
    */
    UPROPERTY(EditAnywhere, Category = Weapon)
    class USphereComponent* SphericChargeZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float BasicAttackSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float ChargeImpulsionForce = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float ChargeExpulseForce = 1500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float ChargeExpulseHeigthRatio = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float WeaponShootForce = 7500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float WeaponShootHeigthRatio = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float PushForce = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
    float WeakZoneDamageMultiplicator = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float MaxRage = 1000.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
    float Rage = 0.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    uint8 MaxLevel = 5;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
    uint8 Level = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
    int32 Score = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
    float DurationOfTheSlowdownEvil = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float WorldSlowingSpeedEvil = 0.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float PlayerSlowingSpeedEvil = 1.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    float Heal = 2.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta=(UIMin = "0.0", UIMax = "1.0"))
    float LosingRageRatioOnDeath = 0.3f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats, meta=(UIMin = "0.0", UIMax = "1.0"))
    float LosingScoreRatioOnDeath = 0.f;


    bool         bTourbillolIsUnlock        = false;
    //bool         bEvilSpellAttackIsUnlock   = false;
    bool         bEvilSpellCapacityIsUnlock = false;
    FTimerHandle MemberTimerEvilCapacity;


public:

    UPROPERTY(EditAnywhere, meta=(UIMin = "0.0", UIMax = "100.0"))
    float RageToUnlockLevel1;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerUpgradLevel1;

    UPROPERTY(EditAnywhere)
    float RageToUnlockLevel2;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerUpgradLevel2;

    UPROPERTY(EditAnywhere)
    float RageToUnlockLevel3;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerUpgradLevel3;

    UPROPERTY(EditAnywhere)
    float RageToUnlockLevel4;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerUpgradLevel4;

    UPROPERTY(EditAnywhere)
    float RageToUnlockLevel5;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerUpgradLevel5;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignature OnPlayerLevelUp;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerTakeRageActionSignature OnPlayerTakeRage;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerTakeScoreActionSignature OnPlayerTakeScore;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerBeginBasicAttackActionSignature OnPlayerBeginBasicAttack;

    //UPROPERTY(BlueprintAssignable)
    //FOnPlayerBasicAttackHitActionSignature OnPlayerBasicAttackHit;

    //UPROPERTY(BlueprintAssignable)
    //FOnPlayerEndBasicAttackActionSignature OnPlayerEndBasicAttack;


    UPROPERTY(BlueprintAssignable)
    FOnPlayerBeginChargeActionSignature OnPlayerBeginCharge;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerChargeHitActionSignature OnPlayerChargeHit;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerEndChargeActionSignature OnPlayerEndCharge;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerBeginTourbilolActionSignature OnPlayerBeginTourbilol;

    //UPROPERTY(BlueprintAssignable)
    //FOnPlayerTourbilolHitActionSignature OnPlayerTourbilolHit;

    //UPROPERTY(BlueprintAssignable)
    //FOnPlayerEndTourbilolActionSignature OnPlayerEndTourbilol;


    UPROPERTY(BlueprintAssignable)
    FOnPlayerBeginEvilCapacityActionSignature OnPlayerBeginEvilCapacity;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerEndEvilCapacityActionSignature OnPlayerEndEvilCapacity;

    UPROPERTY(BlueprintAssignable)
    FOnPlayerBeginSwitchCameraActionSignature OnPlayerBeginSwitchCamera;

private:

    bool bAttacking            = false;
    bool bDoTourbilol          = false;
    bool bCanAttack            = true;
    bool bCanEvilSpellCapacity = true;

protected :
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanDoAction = true;

public:

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Attack)
    class UAnimMontage* Attack;

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    float BaseLookUpRate;

public:
    ABasePlayer();


public:

    UFUNCTION(BlueprintCallable)
    virtual void Tick(float DeltaTime) override;

protected:
    /** Called for forwards/backward input */
    void MoveForward(float Value);

    /** Called for side to side input */
    void MoveRight(float Value);

    /**
    * Called via input to turn at a given rate.
    * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
    */
    void TurnAtRate(float Rate);

    /**
    * Called via input to turn look up/down at a given rate.
    * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
    */
    void LookUpAtRate(float Rate);

    /**
     * @brief Project the enemies give in direction
     */
    UFUNCTION(BlueprintCallable, Category=Character)
    void Charge();

    /**
     * @brief Basic attack with combo
     */
    UFUNCTION(BlueprintCallable, Category=Character)
    void BasicAttack();

    /**
     * @brief Turning attack with displacement controlled by the player like a router
     */
    UFUNCTION(BlueprintCallable, Category=Character)
    void TourbilolAttack();

    /**
    * @brief Can only target Human Torches and Shield Bearers :
    * - Expel Trash Mobs in its path and repel them
    * - Torches explode when launched
    * - Priest have an anti magic barrier and are unaffected
    * - Injury and stun Shields on impact (stun or loss of shield)
    * - Just do damage to the Boss
     */
    UFUNCTION(BlueprintCallable, Category=Character)
    void EvilSpellAttack();

    /**
    * @brief Slow down time and boost the hero. Each enemy hit give life
    */
    UFUNCTION(BlueprintCallable, Category=Character)
    void EvilSpellCapacity();

    /**
    * @brief Chang the camera's side view shoulder 
    */
    UFUNCTION(BlueprintCallable, Category=Character)
    void SwitchCameraMode();

    /**
    * @brief move forward or back ward the camera
    */
    UFUNCTION(BlueprintCallable, Category=Character)
    void MoveCameraArmLength(float FScale) noexcept;

    UFUNCTION(BlueprintCallable, Category=Character)
    void ResetCameraArmLength() noexcept;

protected:
    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // End of APawn interface

    UFUNCTION(BlueprintCallable, Category = Attack)
    void ResetCombo();

    UFUNCTION(BlueprintCallable, Category = Attack)
    void SetCanAttack(bool bNewCanAttack);

    UFUNCTION(BlueprintCallable, Category = Attack)
    void SetCanEvilCapacity();

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult&    SweepResult) override;

    UFUNCTION()
    void OnChargeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32                OtherBodyIndex, bool    bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void Push(AActor* other);

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void ChargeActiveHitBox(bool bIsActive);

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void Stopcharge();

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class UCharacterCameraBoom* GetCameraBoom() const { return CameraBoom; }

    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void TakeRage(float AdditionnalRage) noexcept;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetRage() const noexcept { return Rage; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    bool IsTourbillolIsUnlock() const { return bTourbillolIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    bool EvilSpellIsActive() const { return bCanEvilSpellCapacity; }
    
    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetEvilSpellCapacityIsUnlock(bool bNewEvilSpellCapacityIsUnlock) { bEvilSpellCapacityIsUnlock = bNewEvilSpellCapacityIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetTourbillolIsUnlock(bool bNewTourbillolIsUnlock) { bTourbillolIsUnlock = bNewTourbillolIsUnlock; }
/*
    UFUNCTION(BlueprintCallable, Category = Stats)
    bool IsEvilSpellAttackIsUnlock() const { return bEvilSpellAttackIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetEvilSpellAttackIsUnlock(bool bNewEvilSpellAttackIsUnlock)
    {
        bEvilSpellAttackIsUnlock = bNewEvilSpellAttackIsUnlock;
    }*/

    UFUNCTION(BlueprintCallable, Category = Stats)
    bool IsEvilSpellCapacityIsUnlock() const { return bEvilSpellCapacityIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetEvilSpellCapacityIsUnlock(bool bNewEvilSpellCapacityIsUnlock)
    {
        bEvilSpellCapacityIsUnlock = bNewEvilSpellCapacityIsUnlock;
    }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE float GetRageRatio() const noexcept { return Rage / MaxRage; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void LevelUp() noexcept;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE uint8 GetPlayerLevel() const noexcept { return Level; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE int32 GetScore() const noexcept { return Score; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE bool IsDoTourbilol() const { return bDoTourbilol; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetDoTourbilol(bool bNewDoTourbilol) { bDoTourbilol = bNewDoTourbilol; }
    
    UFUNCTION(BlueprintCallable, Category = Stats)
    void AddScore(int32 AdditionalScore) noexcept;

    virtual void Kill() override;

    void EvilHealing();
};
