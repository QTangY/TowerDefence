// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_EnemyBullet.h"
#include "Character_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Actor_Tower.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AActor_EnemyBullet::AActor_EnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
}
void AActor_EnemyBullet::InitParameter(AActor_Building* Tower, ACharacter_Enemy* E)
{
	AttackedTower = Tower;
	Enemy = E;
}

// Called when the game starts or when spawned
void AActor_EnemyBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActor_EnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackedTower&&Enemy) {
		if (!AttackedTower->isDestory&&!Enemy->isDead) {
			const FVector TowerLocation = AttackedTower->GetActorLocation();
			const FVector BulletLocation = GetActorLocation();
			const FRotator Lr = UKismetMathLibrary::FindLookAtRotation(BulletLocation, TowerLocation);
			const FVector Speed = UKismetMathLibrary::GetForwardVector(Lr) * BulletSpeed;
			ProjectileMovement->SetVelocityInLocalSpace(Speed);
		}
		else {
			Destroy();
		}
	}
	else {
		Destroy();
	}
}

