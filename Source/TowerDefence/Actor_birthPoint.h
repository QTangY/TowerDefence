// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character_Enemy.h"
#include "Actor_birthPoint.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Enemy")
		TSubclassOf<ACharacter_Enemy> EnemyType;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		int Numbers;
};

UCLASS()
class TOWERDEFENCE_API AActor_birthPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_birthPoint();
	UPROPERTY(EditAnywhere, Category = "Gameing")
		class UStaticMeshComponent* birthPoint;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		int EnemyCurWaveNums;
	UPROPERTY(VisibleAnywhere,Category="Gameing")
		ATowerDefenceGameModeBase* GM;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		int EnemyCurNums;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		int thisLevelDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		int XR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		int YR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float EnemySpawnIntervalTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float EnemyWaveSpawnIntervalTime;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		TArray<FEnemyStruct> EnemyTypeAndNums;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timer")
		FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, Category = "Setting")
		class AActor_pathPoint* NextpathPoint;
	UFUNCTION(BlueprintCallable)
		void EnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
