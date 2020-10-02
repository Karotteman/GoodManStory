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
	UPROPERTY(Category = "Stats",VisibleAnywhere, blueprintReadWrite)
	int Life = 100;

	UPROPERTY(Category = "Stats", EditAnywhere, BlueprintReadOnly)
	int LifeMax = 100;

	UPROPERTY(Category = "Stats", EditAnywhere, blueprintReadWrite)
	int Damage = 20;

	UPROPERTY(Category = "Settings", EditAnywhere, blueprintReadWrite)
	bool IsDead = false;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
