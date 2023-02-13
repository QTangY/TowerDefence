// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_TowerDefence.h"
#include "Blueprint/UserWidget.h"
#include "Actor_Tower.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "HUD_TowerDefence.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "DrawDebugHelpers.h"
#include "Misc/OutputDeviceDebug.h" 

EScreenMoveState APlayerController_TowerDefence::CursorMove(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		//屏幕尺寸
		int32 SizeX = INDEX_NONE;
		int32 SizeY = INDEX_NONE;

		//鼠标位置
		float MousePostionX = -107374176.f;
		float MousePostionY = -107374176.f;

		//获取屏幕尺寸
		PlayerController->GetViewportSize(SizeX, SizeY);

		//获取鼠标位置
		PlayerController->GetMousePosition( MousePostionX, MousePostionY);

		if (MousePostionX >= 0 && MousePostionX <= SizeX && MousePostionY >= 0 && MousePostionY <= SizeY)
		{
			float errorValue = 25.0f;
			if (FMath::IsNearlyEqual(MousePostionX, 0.0f, errorValue) && FMath::IsNearlyEqual(MousePostionY, 0.0f, errorValue))
			{

				return EScreenMoveState::Screen_LeftAndUP;
			}
			else if (FMath::IsNearlyEqual(MousePostionX, SizeX, errorValue) && FMath::IsNearlyEqual(MousePostionY, SizeY, errorValue))
			{
				return EScreenMoveState::Screen_RightAndDown;
			}
			else if (FMath::IsNearlyEqual(MousePostionX, SizeX, errorValue) && FMath::IsNearlyEqual(MousePostionY, 0.0f, errorValue))
			{
				return EScreenMoveState::Screen_RightAndUP;
			}
			else if (FMath::IsNearlyEqual(MousePostionX, 0.0f, errorValue) && FMath::IsNearlyEqual(MousePostionY, SizeY, errorValue))
			{
				return EScreenMoveState::Screen_LeftAndDown;
			}
			else if (FMath::IsNearlyEqual(MousePostionX, 0.0f, errorValue))
			{
				return EScreenMoveState::Screen_Left;
			}
			else if (FMath::IsNearlyEqual(MousePostionY, 0.0f, errorValue))
			{
				return EScreenMoveState::Screen_UP;
			}
			else if (FMath::IsNearlyEqual(MousePostionY, SizeY, errorValue))
			{
				return EScreenMoveState::Screen_Down;
			}
			else if (FMath::IsNearlyEqual(MousePostionX, SizeX, errorValue))
			{
				return EScreenMoveState::Screen_Right;
			}
		}
	}
	return EScreenMoveState::Screen_None;
}

bool APlayerController_TowerDefence::MoveDirection(APlayerController* PlayerController, EScreenMoveState ScreenMoveState, float& ScreenMoveSpeed)
{
	FVector OffsetValue = FVector::ZeroVector;
	if (PlayerController && PlayerController->GetPawn())
	{
		switch (ScreenMoveState)
		{
		case Screen_UP:
			OffsetValue = FVector(ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Down:
			OffsetValue = FVector(-ScreenMoveSpeed, 0.0f, 0.0f);
			break;
		case Screen_Right:
			OffsetValue = FVector(0.0f, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_Left:
			OffsetValue = FVector(0.0f, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndUP:
			OffsetValue = FVector(ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_RightAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndUP:
			OffsetValue = FVector(ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		case Screen_LeftAndDown:
			OffsetValue = FVector(-ScreenMoveSpeed, -ScreenMoveSpeed, 0.0f);
			break;
		}
		FVector loca = PlayerController->GetPawn()->GetActorLocation();
		float minX = -3154.0, maxX = 28315.0;
		float minY = -3132.0, maxY = 28305.0;
		FVector newloca = loca + OffsetValue;
		if (newloca.X >= minX && newloca.X <= maxX && newloca.Y >= minY && newloca.Y <= maxY) {
			PlayerController->GetPawn()->AddActorWorldOffset(OffsetValue);
		}
	}
	return OffsetValue != FVector::ZeroVector;
}
void APlayerController_TowerDefence::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	FInputModeGameAndUI InputMode;
	//将鼠标锁定在视口中
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//鼠标始终显示
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	HUDptr = Cast<AHUD_TowerDefence>(GetHUD());
}

void APlayerController_TowerDefence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveDirection(this,CursorMove(this), _ScreenMoveSpeed);
}

void APlayerController_TowerDefence::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftMouseClick",IE_Pressed,this,&APlayerController_TowerDefence::SelectPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &APlayerController_TowerDefence::SelectReleased);

	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &APlayerController_TowerDefence::MovePressed);

	InputComponent->BindAction("Team1", IE_Pressed, this, &APlayerController_TowerDefence::JoinTeam1);
	InputComponent->BindAction("Team2", IE_Pressed, this, &APlayerController_TowerDefence::JoinTeam2);
	InputComponent->BindAction("Team3", IE_Pressed, this, &APlayerController_TowerDefence::JoinTeam3);

	InputComponent->BindAction("UseTeam1", IE_Pressed, this, &APlayerController_TowerDefence::UseTeam1);
	InputComponent->BindAction("UseTeam2", IE_Pressed, this, &APlayerController_TowerDefence::UseTeam2);
	InputComponent->BindAction("UseTeam3", IE_Pressed, this, &APlayerController_TowerDefence::UseTeam3);
}

void APlayerController_TowerDefence::SelectPressed()
{
	HUDptr->InitialPoint = HUDptr->GetMousePos2D();
	HUDptr->StartSeleting = true;
}

void APlayerController_TowerDefence::SelectReleased()
{
	HUDptr->StartSeleting = false;
	for(const auto&A: HUDptr->FoundActor)
	{
		if (Cast<ACharacter_Player>(A))
		{
			SelectActors.Add(A);
		}
		if (Cast<AActor_Building>(A))
		{
			SelectBuildingActors.Add(A);
		}
	}
}

void APlayerController_TowerDefence::MovePressed()
{
	if (SelectActors.Num() > 0) {
		for (int32 i = 0; i < SelectActors.Num(); i++) {
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location + FVector(i / 2 * 500, i % 2 * 500, 0);
			ACharacter_Player* ControllerPeople = Cast<ACharacter_Player>(SelectActors[i]);
			if (ControllerPeople)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(ControllerPeople->GetController(), MoveLocation);
			}
			//DrawDebugSphere(GetWorld(), MoveLocation, 25, 10, FColor::Red, false,3);
		}
	}
}

void APlayerController_TowerDefence::JoinTeam1()
{
	if (SelectActors.Num() > 0) {
		if (ActorTeam1.Num() > 0) {
			ActorTeam1.Empty();
		}
		ActorTeam1 = SelectActors;
	}
}

void APlayerController_TowerDefence::JoinTeam2()
{
	if (SelectActors.Num() > 0) {
		if (ActorTeam2.Num() > 0) {
			ActorTeam2.Empty();
		}
		ActorTeam2 = SelectActors;
	}
}

void APlayerController_TowerDefence::JoinTeam3()
{
	if (SelectActors.Num() > 0) {
		if (ActorTeam3.Num() > 0) {
			ActorTeam3.Empty();
		}
		ActorTeam3 = SelectActors;
	}
}

void APlayerController_TowerDefence::UseTeam1()
{
	if (ActorTeam1.Num() > 0) {
		SelectActors.Empty();
		for (auto Actor : ActorTeam1) {
			if (ActorTeam2.Contains(Actor)) {
				ActorTeam2.Remove(Actor);
				DeSelected(Actor);
			}
			if (ActorTeam3.Contains(Actor)) {
				ActorTeam3.Remove(Actor);
				DeSelected(Actor);
			}
			SelectActors.Add(Actor);
		}
	}
		
}
void APlayerController_TowerDefence::UseTeam2()
{
	if (ActorTeam2.Num()>0) {
		SelectActors.Empty();
		for (auto Actor : ActorTeam2) {
			if (ActorTeam1.Contains(Actor)) {
				ActorTeam1.Remove(Actor);
				DeSelected(Actor);
			}
			if (ActorTeam3.Contains(Actor)) {
				ActorTeam3.Remove(Actor);
				DeSelected(Actor);
			}
			SelectActors.Add(Actor);
		}
	}
	
}
void APlayerController_TowerDefence::UseTeam3()
{
	if (ActorTeam3.Num() > 0) {
		SelectActors.Empty();
		for (auto Actor : ActorTeam3) {
			if (ActorTeam1.Contains(Actor)) {
				ActorTeam1.Remove(Actor);
				DeSelected(Actor);
			}
			if (ActorTeam2.Contains(Actor)) {
				ActorTeam2.Remove(Actor);
				DeSelected(Actor);
			}
			SelectActors.Add(Actor);
		}
	}

}
