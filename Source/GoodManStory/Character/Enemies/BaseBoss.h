// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEnemy.h"
#include "BaseBoss.generated.h"

/**
 * 
 */
UCLASS()
class GOODMANSTORY_API ABaseBoss : public ABaseEnemy
{
    GENERATED_BODY()

protected :

    UPROPERTY(EditAnywhere, Category= "Punch")
    class USphereComponent* PunchZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "Punch")
    float PunchZoneRadius = 1000.f;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* BellyZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "1.0"))
    float BellyZoneHeightRatio = 0.3f;

    /**
     * @brief In second
     */

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnBellyZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnPunchZone;

public : 

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Punch | Attack")
    class UAnimMontage* PunchAttack;

protected :
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "Punch | Attack")
    float PunchSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "Punch | Attack")
    float PunchDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "Punch | Attack")
    float PunchCooldown = 2.f;

protected :

    UPROPERTY(EditAnywhere, Category= "GroundAttack")
    class USphereComponent* ExternChocWaveZone;

    // Add if you want like real choc wave
    //UPROPERTY(EditAnywhere, Category= "GroundAttack")
    //class USphereComponent* InternChocWaveZone;
    
    UPROPERTY(EditAnywhere, Category= "GroundAttack")
    class USphereComponent* GroundAttackZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack")
    float GroundAttackZoneRadius = 1000.f;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* GroundZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "1.0"))
    float GroundZoneHeightRatio = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnGroundZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnGroundAttackZone;

    public : 

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "GroundAttack | Attack")
    class UAnimMontage* GroundAttackAnimMontage;

    protected :
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackDamage = 10.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackChocForce = 5000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackChocForceHeightRatio = 1.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackCooldown = 2.f;

protected :

    virtual void OnHandsObjectsBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult&    SweepResult) override;

    UFUNCTION()
    void OnBellyZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                 const FHitResult&    SweepResult);

    UFUNCTION()
    void OnBellyZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32                OtherBodyIndex);

    UFUNCTION()
    void OnPunchZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                 const FHitResult&    SweepResult);

    UFUNCTION()
    void OnPunchZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32                OtherBodyIndex);

    UFUNCTION()
    void OnGroundZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                             const FHitResult&    SweepResult);

    UFUNCTION()
    void OnGroundZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32                OtherBodyIndex);

    UFUNCTION()
    void OnGroundAttackZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                             const FHitResult&    SweepResult);

    UFUNCTION()
    void OnGroundAttackZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* 
    OtherComp,
                               int32                OtherBodyIndex);


    virtual void BeginPlay() override;
    
public :

    ABaseBoss();

    UFUNCTION(BlueprintCallable)
    void Punch() noexcept;

    UFUNCTION(BlueprintCallable)
    void GroundAttack() noexcept;

    UFUNCTION(BlueprintCallable)
    void DoChocWave() noexcept;
};
