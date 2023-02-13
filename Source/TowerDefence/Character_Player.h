// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Player.generated.h"

// UENUM(BlueprintType)
// enum EScreenMoveState
// {
// 	Screen_None,
// 	Screen_UP,			//上
// 	Screen_Down,			//下
// 	Screen_Right,			//左
// 	Screen_Left,			//右
// 	Screen_RightAndUP,		//左上
// 	Screen_RightAndDown,	        //左下
// 	Screen_LeftAndUP,		//右上
// 	Screen_LeftAndDown,		//右下
// 	Screen_MAX
// };

UCLASS()
class TOWERDEFENCE_API ACharacter_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Player();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
