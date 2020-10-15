// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABasePlayer : public ABaseCharacter
{
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    class UCharacterCameraBoom* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, Category = Camera)
    class UCameraComponent* FollowCamera;

    class UMaterialInstanceDynamic* DynMaterial;

    UPROPERTY(EditAnywhere, Category = Weapon)
    class UStaticMeshComponent* Weapon;

public :
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
    class UBoxComponent* BoxWeapon;
    
private:
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

    UPROPERTY(EditAnywhere, Category = Weapon)
    float ChargeImpulsionForce = 100.f;
    
    UPROPERTY(EditAnywhere, Category = Weapon)
    float Dammage = 20.f;

    UPROPERTY(EditAnywhere, Category = Stats)
    float MaxRage = 1000.f;

    UPROPERTY(VisibleAnywhere, Category = Stats)
    float Rage = 0.f;

    UPROPERTY(Category = Stats, EditAnywhere)
    uint8 MaxLevel = 3;

    UPROPERTY(VisibleAnywhere, Category = Stats)
    uint8 Level = 0;

    bool bAttacking = false;
    bool bCanAttack = true;

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

    UFUNCTION()
    void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32                OtherBodyIndex, bool    bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnChargeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32                OtherBodyIndex, bool    bFromSweep, const FHitResult& SweepResult);

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
    FORCEINLINE float GetRageRatio() const noexcept { return Rage / MaxRage; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void LevelUp() noexcept;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE uint8 GetPlayerLevel() const noexcept { return Level; }

    virtual void Kill() override;
};
