// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TowerDefenceGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ATowerDefenceGameModeBase : public AGameMode
{	
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Setting")
		int  Max_Money;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		int RecoverHP;
	UPROPERTY(VisibleAnywhere, Category = Gameing)
		bool isFail;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameing)
		bool isWin;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameing)
		int  Cur_Money;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		bool EnemyisSpawned;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		int SceneEnemyNumbers;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Gameing)
		class AActor_Base* AlineBase;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Gameing)
		bool isBuilding;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameing)
		FTimerHandle MoveTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameing)
		class AActor_Building* myBuilding;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameing)
		class APlayerController_TowerDefence* TPC;
	UPROPERTY(EditAnywhere,Category = Gameing)
		UUserWidget* GameOver_Widget;
	UPROPERTY(EditAnywhere, Category = Gameing)
		TSubclassOf<UUserWidget> GameOver_WidgetClass;
	UFUNCTION(BlueprintCallable,Category=Building)
		void Build(TSubclassOf<AActor_Building> Building);
	UFUNCTION(BlueprintCallable)
		void ActorMove();
	UFUNCTION(BlueprintCallable)
		void GameOver();
	UFUNCTION(BlueprintCallable)
		void DestroyEnemy();
	UFUNCTION(BlueprintCallable)
		void OpenGameBilling();
	UFUNCTION(BlueprintCallable)
		void AddMoney(int Money);
	UFUNCTION(BlueprintCallable)
		void VictoryConditions();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
