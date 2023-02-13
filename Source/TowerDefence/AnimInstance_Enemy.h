// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UAnimInstance_Enemy : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperty)
		void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class ACharacter_Enemy* _Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* _Pawn;

};
