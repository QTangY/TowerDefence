// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Enemy.h"
#include "Character_Enemy.h"

void UAnimInstance_Enemy::NativeInitializeAnimation()
{
	if (!_Pawn) {
		_Pawn = TryGetPawnOwner();
	}
	_Enemy = Cast<ACharacter_Enemy>(_Pawn);
}


void UAnimInstance_Enemy::UpdateAnimationProperties()
{
	if (!_Pawn) {
		_Pawn = TryGetPawnOwner();
	}
	if (_Pawn) {
		FVector Speed = _Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0);
		MovementSpeed = LateralSpeed.Size();
	}
}
