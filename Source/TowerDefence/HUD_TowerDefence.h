// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_TowerDefence.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API AHUD_TowerDefence : public AHUD
{
	GENERATED_BODY()
public:
	FVector2D InitialPoint;
	FVector2D CurrentPoint;
	bool StartSeleting;
	void virtual DrawHUD() override;
	FVector2D GetMousePos2D();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TArray<AActor*>FoundActor;
};
