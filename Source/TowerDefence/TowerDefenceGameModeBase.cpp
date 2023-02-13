// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameModeBase.h"
#include "Character_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController_TowerDefence.h"
#include "Blueprint/UserWidget.h"
#include "Actor_Base.h"
#include "Actor_Tower.h"
#include "Actor_Building.h"

void ATowerDefenceGameModeBase::Build(TSubclassOf<AActor_Building> Building)
{
	isBuilding = true;
	FVector WorldLocation;
	FVector WorldDirection;
	if (TPC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("WorldDirection is %s"), *WorldDirection.ToString());
		FHitResult Hit;
		FVector startLocation;
		FVector endLocation;
		startLocation = WorldLocation;
		endLocation = startLocation + WorldDirection * 1000000;
		TArray<AActor*> ignorArray;
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), startLocation, endLocation, 5.0, ETraceTypeQuery::TraceTypeQuery3, false, ignorArray, EDrawDebugTrace::None, Hit, true);
		if (Building) {
			myBuilding = GetWorld()->SpawnActor<AActor_Building>(Building,Hit.Location, FRotator(0.0f));
			myBuilding->ChangeMat();
		}
		GetWorldTimerManager().SetTimer(MoveTimer, this, &ATowerDefenceGameModeBase::ActorMove, 0.01, true);
	}
}

void ATowerDefenceGameModeBase::ActorMove()
{
	FVector WorldLocation;
	FVector WorldDirection;
	if (TPC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
		FHitResult Hit;
		FVector startLocation;
		FVector endLocation;
		startLocation = WorldLocation;
		endLocation = startLocation + WorldDirection * 1000000;
		TArray<AActor*> ignorArray;
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), startLocation, endLocation, 5.0, ETraceTypeQuery::TraceTypeQuery3, false, ignorArray, EDrawDebugTrace::None, Hit, true);
		if (myBuilding) {
			myBuilding->SetActorLocation(Hit.Location);
		}	
	}
}

void ATowerDefenceGameModeBase::GameOver()
{
	if (isFail) {
		DestroyEnemy();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "OpenGameBilling"; //function名
		LatentInfo.Linkage = 1;
		LatentInfo.UUID = 100;
		UKismetSystemLibrary::Delay(GetWorld(), 5.0f, LatentInfo);
	}
	else {
		if (isWin) {
			DestroyEnemy();
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "OpenGameBilling"; //function名
			LatentInfo.Linkage = 1;
			LatentInfo.UUID = 100;
			UKismetSystemLibrary::Delay(GetWorld(), 5.0f, LatentInfo);
		}
	}
}

void ATowerDefenceGameModeBase::DestroyEnemy()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter_Enemy::StaticClass(), Enemies);
	for (auto Enemy : Enemies) {
		ACharacter_Enemy* e;
		e=Cast<ACharacter_Enemy>(Enemy);
		e->isDead = true;
		e->onDie();
	}
}

void ATowerDefenceGameModeBase::OpenGameBilling()
{
	GameOver_WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/Game/BulePrint/UI/GameOver_UI.GameOver_UI_C'"));
	if (GameOver_WidgetClass) {
		GameOver_Widget = CreateWidget<UUserWidget>(GetWorld(), GameOver_WidgetClass);
		if (GameOver_Widget) {
			GameOver_Widget->AddToViewport();
			//隐藏鼠标
			TPC->bShowMouseCursor = true;
			//设置输入模式
			FInputModeUIOnly InputUIOnly;
			InputUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			TPC->SetInputMode(InputUIOnly);
		}
	}
}

void ATowerDefenceGameModeBase::AddMoney(int Money)
{
	Cur_Money += Money;
}

void ATowerDefenceGameModeBase::VictoryConditions()
{
	if (!isFail) {
		if (EnemyisSpawned&&SceneEnemyNumbers<=0) {
			isWin = true;
		}
	} 
}

void ATowerDefenceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	isFail = false;
	isWin = false;
	EnemyisSpawned = false;
	SceneEnemyNumbers = 0;
	Cur_Money = Max_Money;
	TPC = Cast<APlayerController_TowerDefence>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor_Base::StaticClass(), Actors);
	if (Actors.Num()) {
		AlineBase = Cast<AActor_Base>(Actors[0]);
	}

}
