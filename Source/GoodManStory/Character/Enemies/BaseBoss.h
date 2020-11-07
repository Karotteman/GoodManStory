// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Utility/Utility.h>


#include "BaseEnemy.h"
#include "BaseBoss.generated.h"

UDELEGATE(BlueprintAuthorityOnly)DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnLevelUpActionSignatureBoss, int, CurrentLevel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPunchActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundAttackActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChocWaveActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireBallThrowActionSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireBallAttackBeginActionSignature);

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GOODMANSTORY_API ABaseBoss : public ABaseEnemy
{
    GENERATED_BODY()

protected :

    UPROPERTY(EditAnywhere)
    class USphereComponent* HeadCollision;
    
    UPROPERTY(EditAnywhere, Category= "Punch | Attack")
    class USphereComponent* PunchZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "Punch | Attack")
    float PunchZoneRadius = 1000.f;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* BellyZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "1.0"))
    float BellyZoneHeightRatio = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "FireBall | Attack")
    float FireBallDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "FireBall | Attack")
    float FireBallVelocity = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "FireBall | Attack")
    float FireBallScale = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "FireBall | Attack")
    float FireBallAttackCoolDown = 3.f;

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "FireBall | Attack")
    class UAnimMontage* FireBallAttackSpeedAnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "FireBall | Attack")
    float FireBallAttackSpeed = 1.f;

    UPROPERTY(EditAnywhere, Category= "FireBall | Attack")
    TSubclassOf<class AFireBall> FireBallType = nullptr;

    UPROPERTY(EditAnywhere, Category= "FireBall | Attack")
    FName FireBallSpawningBoneName = TEXT("hand_l");

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignatureBoss OnUpgradLevel1;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignatureBoss OnUpgradLevel2;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignatureBoss OnUpgradLevel3;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignatureBoss OnUpgradLevel4;

    UPROPERTY(BlueprintAssignable)
    FOnLevelUpActionSignatureBoss OnUpgradLevel5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
    float StatsForLevel1 = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
    float StatsForLevel2 = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
    float StatsForLevel3 = 3000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
    float StatsForLevel4 = 5000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
    float StatsForLevel5 = 10000.f;

public :

    UPROPERTY(BlueprintAssignable)
    FOnPunchActionSignature OnPunch;

    UPROPERTY(BlueprintAssignable)
    FOnGroundAttackActionSignature OnGroundAttack;

    UPROPERTY(BlueprintAssignable)
    FOnChocWaveActionSignature OnChocWave;

    UPROPERTY(BlueprintAssignable)
    FOnFireBallThrowActionSignature OnFireBallThrow;

    UPROPERTY(BlueprintAssignable)
    FOnFireBallAttackBeginActionSignature OnFireBallAttackBegin;

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

    UPROPERTY(Category = Stats, EditAnywhere)
    uint8 MaxLevel = 5;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
    uint8 Level = 0;

protected :

    UPROPERTY(EditAnywhere, Category= "GroundAttack")
    class USphereComponent* ExternChocWaveZone;

    // Add if you want like real choc wave
    //UPROPERTY(EditAnywhere, Category= "GroundAttack")
    //class USphereComponent* InternChocWaveZone;

    UPROPERTY(EditAnywhere, Category= "GroundAttack")
    class USphereComponent* GroundAttackZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack")
    float GroundAttackZoneRadius = 300.f;

    UPROPERTY(EditAnywhere)
    class UBoxComponent* GroundZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0", UIMax = "1.0"))
    float GroundZoneHeightRatio = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnGroundZone = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsOnGroundAttackZone = false;

public :

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "GroundAttack | Attack")
    class UAnimMontage* GroundAttackAnimMontage;

protected :

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackChocForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackChocForceHeightRatio = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = "0.0"), Category= "GroundAttack | Attack")
    float GroundAttackCooldown = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "ChocWave")
    bool ChocForceDependingOfDistance = true;

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
    void OnGroundAttackZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32        OtherBodyIndex);


    virtual void BeginPlay() override;

public :

    ABaseBoss();

    UFUNCTION(BlueprintCallable)
    void Punch() noexcept;

    UFUNCTION(BlueprintCallable)
    void GroundAttack() noexcept;

    UFUNCTION(BlueprintCallable)
    void FireBallAttack() noexcept;

    UFUNCTION(BlueprintCallable)
    void ThrowFireBall() noexcept;

    UFUNCTION(BlueprintCallable)
    void DoChocWave() noexcept;

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetLevel(uint8 NewLevel) noexcept;

    UFUNCTION(BlueprintCallable, Category = Stats)
    FORCEINLINE uint8 GetBossLevel() const noexcept { return Level; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetPunchCooldown() const { return PunchCooldown; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetPunchCooldown(float NewPunchCooldown) { PunchCooldown = NewPunchCooldown; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetGroundAttackCooldown() const { return GroundAttackCooldown; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetGroundAttackCooldown(float NewGroundAttackCooldown) { GroundAttackCooldown = NewGroundAttackCooldown; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetFireBallDamage() const { return FireBallDamage; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallDamage(float NewFireBallDamage) { FireBallDamage = NewFireBallDamage; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetFireBallVelocity() const { return FireBallVelocity; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallVelocity(float NewFireBallVelocity) { FireBallVelocity = NewFireBallVelocity; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetFireBallScale() const { return FireBallScale; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallScale(float NewFireBallScale) { FireBallScale = NewFireBallScale; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetFireBallAttackCoolDown() const { return FireBallAttackCoolDown; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallAttackCoolDown(float NewFireBallAttackCoolDown)
    {
        FireBallAttackCoolDown = NewFireBallAttackCoolDown;
    }

    UFUNCTION(BlueprintCallable, Category = Stats)
    float GetFireBallAttackSpeed() const { return FireBallAttackSpeed; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallAttackSpeed(float NewFireBallAttackSpeed) { FireBallAttackSpeed = NewFireBallAttackSpeed; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    TSubclassOf<AFireBall> GetFireBallType() const { return FireBallType; }

    UFUNCTION(BlueprintCallable, Category = Stats)
    void SetFireBallType(const TSubclassOf<AFireBall>& NewFireBallType) { FireBallType = NewFireBallType; }
};
