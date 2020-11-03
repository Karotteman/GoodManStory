// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

class UArrowComponent;

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireBallSpawnActionSignature);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireBallDestroyActionSignature);

UCLASS()
class GOODMANSTORY_API AFireBall : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* Collider;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Mesh;

    UPROPERTY(BlueprintAssignable)
    FOnFireBallSpawnActionSignature OnFireBallSpawn;

    UPROPERTY(BlueprintAssignable)
    FOnFireBallDestroyActionSignature OnFireBallDestroy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.f;
    
#if WITH_EDITORONLY_DATA
    /** Component shown in the editor only to indicate character facing */
    UPROPERTY()
    UArrowComponent* ArrowComponent;

#endif


public:
    // Sets default values for this actor's properties
    AFireBall();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnFireBallBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32        OtherBodyIndex, bool bFromSweep,
                                const FHitResult&    SweepResult);
public:
    virtual void BeginDestroy() override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void Throw(float Force);

    UFUNCTION(BlueprintCallable)
    FORCEINLINE float GetDamage() const { return Damage; }
    
    UFUNCTION(BlueprintCallable)
    void  SetDamage(float NewDamage) { Damage = NewDamage; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE float GetRadius() const { return Collider->GetScaledSphereRadius(); }
    
    UFUNCTION(BlueprintCallable)
    void  SetRadius(float NewRadius) { Collider->SetSphereRadius(NewRadius); }
    
};
