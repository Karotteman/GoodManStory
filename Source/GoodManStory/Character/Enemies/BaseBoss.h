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

	public:
    
	ABaseBoss();
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Shield;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxShield;

	protected:
    
	UFUNCTION()
    void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32                OtherBodyIndex, bool    bFromSweep, const FHitResult& SweepResult);

	public:
	virtual AActor* DropWeapon() override;
    
	virtual void Kill() override;
};
