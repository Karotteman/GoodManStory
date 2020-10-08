// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GOODMANSTORY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(Category = Stats, EditAnywhere, BlueprintReadOnly)
	float LifeMax = 100.f;
	
	UPROPERTY(Category = Stats,VisibleAnywhere, blueprintReadWrite)
	float Life = LifeMax;

	UPROPERTY(Category = Stats, EditAnywhere, blueprintReadWrite)
	float Damage = 20.f;

	UPROPERTY(Category = Settings, EditAnywhere, blueprintReadWrite)
	bool IsDead = false;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* @brief Function to inflict dammage to player
	* @param dammage 
	* @return 
	*/
	UFUNCTION(BlueprintCallable, Category = "Life")
    void TakeDammage(float Dammage) noexcept;

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

};
