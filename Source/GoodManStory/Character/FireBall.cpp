// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"

#include <Utility/Utility.h>

#include "Components/ArrowComponent.h"
#include "Components/SkinnedMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Players/BasePlayer.h"

#define COLLISION_CHANNEL_PLAYER ECC_GameTraceChannel1
#define COLLISION_CHANNEL_FIREBALL ECC_GameTraceChannel4

void AFireBall::OnFireBallBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnFireBallHitActor.Broadcast(OtherActor);
	ABasePlayer* pPlayer = Cast<ABasePlayer>(OtherActor);

	if (pPlayer)
	{
		OnFireBallHitPlayer.Broadcast(pPlayer);
		pPlayer->TakeDamageCharacter(Damage);
	}

	if (!DestroyOnlyIfGroundTagFound || OtherComp->ComponentHasTag(TEXT("FireBallDestroyable")))
	{
		Destroy();
	}
}

void AFireBall::Destroyed()
{
	Super::Destroyed();
	OnFireBallDestroy.Broadcast();
}

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->InitSphereRadius(40.f);
	//Collider->SetCollisionProfileName();

	Collider->CanCharacterStepUpOn = ECB_No;
	Collider->SetShouldUpdatePhysicsVolume(true);
	Collider->SetCanEverAffectNavigation(false);
	Collider->bDynamicObstacle = true;
	Collider->SetSimulatePhysics(true);
	Collider->SetEnableGravity(false);
	
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionResponseToChannel(COLLISION_CHANNEL_PLAYER, ECollisionResponse::ECR_Overlap);

	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetCollisionObjectType(COLLISION_CHANNEL_FIREBALL);
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnFireBallBeginOverlap);
	Collider->SetGenerateOverlapEvents(true);
	RootComponent = Collider;
	
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(Collider);
		ArrowComponent->bIsScreenSizeScaled = true;
	}
#endif // WITH_EDITORONLY_DATA\

	
	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(Collider);

		//Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();

	SpawnPoint = GetActorLocation();
	OnFireBallSpawn.Broadcast();
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((GetActorLocation() - SpawnPoint).SizeSquared() > MaxRangeLife * MaxRangeLife)
		Destroy();
}

void AFireBall::Throw(float Force)
{
	Collider->AddImpulse(GetActorForwardVector() * Force, NAME_None, true);
}

