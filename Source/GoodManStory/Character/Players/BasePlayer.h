// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "Components/TimelineComponent.h"

#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABasePlayer : public ABaseCharacter
{
    GENERATED_BODY()

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCharacterCameraBoom* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    class UMaterialInstanceDynamic* DynMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
    TArray<UAnimMontage*> SlotAnimationsAttackCombo;

    uint8 BasicAttackComboCount = 0;

public:
    ABasePlayer();

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
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

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class UCharacterCameraBoom* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
