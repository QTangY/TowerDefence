// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Enemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemy_Property
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float AttackSpeed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float PhysicalAttackValue;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float MagicAttackValue;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float PhysicalDefense;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float MagicDefense;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			int Enemy_AttackDistance;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float MaxHP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
			float ArriveEndDamage;
};

UENUM(BlueprintType)
enum class EMoveStatus : uint8 {
	MS_MoveToBase		UMETA(DisplayName = "MoveToBase"),
	MS_MoveToTarget		UMETA(DisplayName = "MoveToTarget"),
	MS_Attacking		UMETA(DisplayName = "Attacking"),
};

UCLASS()
class TOWERDEFENCE_API ACharacter_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Enemy();
	TSet<AActor*> IgnoreDeleteActors;
	TSet<AActor*> IgnoreAttackActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSet<AActor*> deleteOverlappingActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSet<AActor*> attackOverlappingActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		FEnemy_Property Property;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		EMoveStatus MoveStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gameing")
		bool isDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		float CurHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		int Distance;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		class AAIController* EnemyController;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		class APlayerController_TowerDefence* PlayerController;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		class ATowerDefenceGameModeBase* GM;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		class AActor_birthPoint* FirstPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		class AActor_Building* AttackTower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameing")
		class AActor_Building* TargetRole;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		FTimerHandle WaitForStartTimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* AttackSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		bool isAttacking;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		class APlayerController_TowerDefence* MainPlayerController;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		FTimerHandle TowerDetectTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float Enemy_DetectRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float Enemy_DetectInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		int Value;
	UPROPERTY(EditAnywhere, Category = "Setting")
		int seed;
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable)
		void Attack();
	UFUNCTION(BlueprintCallable)
		void MoveToBase();
	UFUNCTION(BlueprintCallable)
		void ArriveEnd();
	UFUNCTION(BlueprintCallable)
		void Death();
	UFUNCTION(BlueprintCallable)
		void HitResult();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> DamageTypeClass;
	UPROPERTY()
		TSubclassOf<AActor_Building> AT;
	UFUNCTION(BlueprintImplementableEvent)
		void onDie();
	UFUNCTION(BlueprintCallable)
		void Detection();
	UFUNCTION(BlueprintCallable)
		void StartDetection();
	UFUNCTION(BlueprintCallable)
		void Action();
	UFUNCTION(BlueprintCallable)
		void SetFaceToTarget(AActor* Target, float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void MoveToTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
