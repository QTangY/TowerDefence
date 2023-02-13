// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_Bullet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Actor_Tower.h"
#include "Character_Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AActor_Bullet::AActor_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
}

void AActor_Bullet::InitParameter(ACharacter_Enemy*Enemy, AActor_Tower* T)
{
		AttackedEnemy = Enemy;
		Tower = T;
}

// Called when the game starts or when spawned
void AActor_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActor_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackedEnemy&&Tower) {
		if (!AttackedEnemy->isDead&&!Tower->isDestory) {
			FVector EnemyLocation= AttackedEnemy->GetActorLocation();
			FVector BulletLocation = GetActorLocation();
			FRotator Lr=UKismetMathLibrary::FindLookAtRotation(BulletLocation, EnemyLocation);
			FVector Speed = UKismetMathLibrary::GetForwardVector(Lr) * BulletSpeed;
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

