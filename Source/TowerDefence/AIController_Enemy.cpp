// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Enemy.h"
#include "Character_Enemy.h"
#include "Actor_pathPoint.h"
#include "Actor_birthPoint.h"

void AAIController_Enemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
 	Enemy = Cast<ACharacter_Enemy>(GetPawn());
	if (Enemy) 
	{
		Enemy->StartDetection();
	}

// 	if (!Enemy->AttackTower) {
// 		Enemy->ArriveEnd();
// 	}
	
// 
// 	if (Enemy)
// 	{
// 		if (Enemy->NextPoint->NextPoint)
// 		{
// 			Enemy->NextPoint = Enemy->NextPoint->NextPoint;
// 			Enemy->Move();
// 		}
// 		else {
// 			Enemy->ArriveEnd();
// 		}
// 	}
}

