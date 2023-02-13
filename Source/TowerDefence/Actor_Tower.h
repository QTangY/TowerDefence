// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character_Enemy.h"
#include "Actor_Base.h"
#include "Actor_Bullet.h"
#include "Actor_Building.h"
#include "Actor_Tower.generated.h"

USTRUCT(BlueprintType)
struct FTower_Property
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float AttackInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float PhysicalAttackValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float MagicAttackValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float PhysicalDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float MagicDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		int AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		int MaxAttackEnemyNum;
};

UCLASS()
class TOWERDEFENCE_API AActor_Tower : public AActor_Building
{
	GENERATED_BODY()

public:
	TSet<AActor* > IgnoreActors;
	AActor_Tower();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Base;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* myGun;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* Muzzle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Halo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		float DetectionInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerStting")
		TArray<TSubclassOf<AActor_Bullet>>SpawnBullets;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gaming")
		TSet<AActor*> DetectedTotalEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gaming")
		TSet<ACharacter_Enemy*>   AttackedEnemyArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gaming")
		bool CanAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		FTower_Property Property;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		bool isAttacking;
private:
	UPROPERTY(VisibleAnywhere, Category = "Gaming")
		FTimerHandle DetectionTimer;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		TArray<UMaterialInterface*> MBase;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		TArray<UMaterialInterface*> MGun;
	UFUNCTION(BlueprintCallable)
		void EnemyDetection();
	UFUNCTION(BlueprintCallable)
		void Attack();
	UFUNCTION(BlueprintCallable)
		void StartCheck();

	virtual void upGrade() override;
	virtual void ChangeMat() override;
	virtual void ForbidPut() override;
	virtual void AllowPut() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
		void FireBullet();

};

