// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GoodManStory/Character/BaseWarrior.h"
#include "PhysicsEngine/RadialForceComponent.h"

#include "BasePlayer.generated.h"

UDELEGATE(BlueprintAuthorityOnly)DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnLevelUpActionSignature, int, CurrentLevel);

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

    uint8 BasicAttackComboCount = 0;

    /**
    * @brief This collider is use when player use its feature "Charge"
    */
    UPROPERTY(EditAnywhere, Category = Weapon)
    class USphereComponent* SphericChargeZone;

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

    bool bTourbillolIsUnlock      = false;
    bool bEvilSpellAttackIsUnlock = false;

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

private:
    bool bAttacking = false;
    bool bCanAttack = true;
    bool bCanCharge = true;

public:
    ABasePlayer();

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    float BaseLookUpRate;

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
    void EvilSpellCapcity();

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
    void SetCanCharge(bool bNewCanCharge);

    virtual void OnRightHandObjectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                      const FHitResult&    SweepResult) override;

    UFUNCTION()
    void OnChargeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32                OtherBodyIndex, bool    bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void Push(AActor* other);

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void ChargeActiveHitBox(bool bIsActive);

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
    void SetTourbillolIsUnlock(bool bNewTourbillolIsUnlock) { bTourbillolIsUnlock = bNewTourbillolIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    bool IsEvilSpellAttackIsUnlock() const { return bEvilSpellAttackIsUnlock; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetEvilSpellAttackIsUnlock(bool bNewEvilSpellAttackIsUnlock)
    {
        bEvilSpellAttackIsUnlock = bNewEvilSpellAttackIsUnlock;
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
    void AddScore(int32 AdditionalScore) noexcept { Score += AdditionalScore; }

    virtual void Kill() override;
};
