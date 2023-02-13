// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Wall.h"
#include "PlayerController_TowerDefence.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
AActor_Wall::AActor_Wall()
{
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	RootComponent = Root;
	W_HP = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP"));
	W_BuildingBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingBar"));
	C_PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PS"));
	C_Chassis = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chassis"));
	Collsion = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion"));
	Wall->SetupAttachment(Root);
	W_HP->SetupAttachment(RootComponent);
	W_BuildingBar->SetupAttachment(RootComponent);
	C_PaperSprite->SetupAttachment(RootComponent);
	C_Chassis->SetupAttachment(RootComponent);
	Collsion->SetupAttachment(RootComponent);
}

void AActor_Wall::upGrade()
{
	if (Building_CurLevel == Building_MaxLavel) {
		isMaxLevel = true;
	}
	if (!isMaxLevel) {
		Building_CurLevel++;
		UpGradeMoney = Building_CurLevel * UpGradeMoney;
		SellPrice = Building_CurLevel * SellPrice;
		float HpRate = BuildingCur_HP / Property.MaxHP;
		Property.MaxHP *= 2;
		BuildingCur_HP = Property.MaxHP * HpRate;
	}
}

void AActor_Wall::ChangeMat()
{
	int n = M_Wall.Num();
	APlayerController_TowerDefence* Pc = Cast<APlayerController_TowerDefence>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (A) {
		A = !A;
		SetActorEnableCollision(false);
		Pc->bEnableClickEvents = 0;
		for (int i = 0; i < n; i++) {
			Wall->SetMaterial(i, UnMat);
		}
	}
	else {
		A = !A;
		SetActorEnableCollision(true);
		for (int i = 0; i < n; i++)
		{
			Wall->SetMaterial(i, M_Wall[i]);
		}
	}
}

void AActor_Wall::ForbidPut()
{
	int n = M_Wall.Num();
	for (int i = 0; i < n; i++) {
		Wall->SetMaterial(i, ForbidPutMat);
	}
}

void AActor_Wall::AllowPut()
{
	int n = M_Wall.Num();
	for (int i = 0; i < n; i++) {
		Wall->SetMaterial(i, UnMat);
	}
}

void AActor_Wall::BeginPlay()
{
	Super::BeginPlay();
	M_Wall = Wall->GetMaterials();
	BuildingCur_HP = Property.MaxHP;
	A = true;
	isBuilt = false;
	isMaxLevel = false;
	isDestory = false;
	Building_CurLevel = 1;
}

float AActor_Wall::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float PhysicsHarmRelief = Property.PhysicsDefense / (602 + Property.PhysicsDefense);
	int Damage = DamageAmount * PhysicsHarmRelief;
	if (BuildingCur_HP > Damage) {
		BuildingCur_HP -= Damage;
	}
	else {
		BuildingCur_HP = 0;
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		isDestory = true;
		Destroy();
	}
	return Damage;
}
