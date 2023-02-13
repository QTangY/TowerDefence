// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_TowerDefence.h"



void AHUD_TowerDefence::DrawHUD()
{
	if (StartSeleting) {
		FoundActor.Empty();
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0, 1, 0, .15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsInSelectionRectangle<AActor>(InitialPoint, CurrentPoint, FoundActor, false, false);
	}
}

FVector2D AHUD_TowerDefence::GetMousePos2D()
{
	float PosX;
	float PosY;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}
