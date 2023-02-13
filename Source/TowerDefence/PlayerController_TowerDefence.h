// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character_Player.h"
#include "PlayerController_TowerDefence.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EScreenMoveState
{
	Screen_None,
	Screen_UP,			//上
	Screen_Down,			//下
	Screen_Right,			//左
	Screen_Left,			//右
	Screen_RightAndUP,		//左上
	Screen_RightAndDown,	        //左下
	Screen_LeftAndUP,		//右上
	Screen_LeftAndDown,		//右下
	Screen_MAX
};

UCLASS()
class TOWERDEFENCE_API APlayerController_TowerDefence : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	EScreenMoveState CursorMove(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable)
	bool MoveDirection(APlayerController* PlayerController,EScreenMoveState ScreenMoveState, float& ScreenMoveSpeed);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _ScreenMoveSpeed;
	UPROPERTY()
	class AHUD_TowerDefence*HUDptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*>SelectActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*>SelectBuildingActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*>ActorTeam1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*>ActorTeam2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*>ActorTeam3;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Selected(AActor*p);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void DeSelected(AActor* p);
	void SelectPressed();
	void SelectReleased();
	void MovePressed();
	void JoinTeam1();
	void JoinTeam2();
	void JoinTeam3();
	void UseTeam1();
	void UseTeam2();
	void UseTeam3();
protected:
	void virtual BeginPlay() override;
	void virtual Tick(float DeltaTime) override;
	void virtual SetupInputComponent() override;
};
