// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_EnemyBullet.generated.h"

UCLASS()
class TOWERDEFENCE_API AActor_EnemyBullet : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AActor_EnemyBullet();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Setting")
		float BulletSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float BulletDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float DamageRange;
	UPROPERTY(BlueprintReadWrite ,Category = "Gameing")
		class AActor_Building* AttackedTower;
	UPROPERTY( BlueprintReadWrite,Category = "Gameing")
		class ACharacter_Enemy* Enemy;
	// 攻击伤害类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> DamageTypeClass;
	UFUNCTION(BlueprintCallable)
		void InitParameter(AActor_Building* Tower, ACharacter_Enemy* E);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
