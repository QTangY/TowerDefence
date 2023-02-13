// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Enemy.generated.h"

UCLASS()
class TOWERDEFENCE_API AAIController_Enemy : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ACharacter_Enemy* Enemy;
public:
	void virtual OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)override;
};
