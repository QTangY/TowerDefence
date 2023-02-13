// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor_Tower.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController_TowerDefence.h"
#include "TowerDefenceGameModeBase.h"
#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"
// Sets default values

AActor_Tower::AActor_Tower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Base = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base"));
	myGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Muzzle = CreateDefaultSubobject<UBoxComponent>(TEXT("Muzzle"));
	Halo=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Halo"));
	W_HP= CreateDefaultSubobject<UWidgetComponent>(TEXT("HP"));
	W_BuildingBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingBar"));
	C_PaperSprite= CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PS"));
	C_Chassis= CreateDefaultSubobject<UChildActorComponent>(TEXT("Chassis"));
	Collsion= CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion"));
	RootComponent= Root;
	Base->SetupAttachment(Root);
	myGun->SetupAttachment(Base);
	Muzzle->SetupAttachment(myGun);
	Halo->SetupAttachment(Base);
	W_HP->SetupAttachment(RootComponent);
	W_BuildingBar->SetupAttachment(RootComponent);
	C_PaperSprite->SetupAttachment(RootComponent);
	C_Chassis->SetupAttachment(RootComponent);
	Collsion->SetupAttachment(RootComponent);
}


void AActor_Tower::upGrade()
{
	if (Building_CurLevel == Building_MaxLavel) {
		isMaxLevel = true;
	}
	if (!isMaxLevel) {
		Building_CurLevel++;
		UpGradeMoney = Building_CurLevel * UpGradeMoney;
		SellPrice = Building_CurLevel * SellPrice;
		Property.PhysicalAttackValue += 1;
		Property.AttackRange *= 1.25;
		Property.AttackInterval /= 1.25;
		const float HpRate = BuildingCur_HP / Property.MaxHP;
		Property.MaxHP *= 2;
		BuildingCur_HP = Property.MaxHP * HpRate;
	}
}

void AActor_Tower::StartCheck()
{
	GetWorldTimerManager().SetTimer(DetectionTimer, this, &AActor_Tower::EnemyDetection, DetectionInterval, true);
	DetectedTotalEnemy.Empty();
	IgnoreActors.Empty();
}

void AActor_Tower::EnemyDetection()
{
	ATowerDefenceGameModeBase* GM = Cast<ATowerDefenceGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	const FVector Start = GetActorLocation();
	const FVector End = Start+10;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery7);
	TArray<FHitResult> HitResults;
	const bool bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, Property.AttackRange, ObjectTypes, false, IgnoreActors.Array(), EDrawDebugTrace::None, HitResults, true);
	if (bIsHit && isBuilt)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (HitResult.Actor!=nullptr)
			{
				DetectedTotalEnemy.Add(Cast<ACharacter_Enemy>(HitResult.Actor));
				IgnoreActors.Add(Cast<ACharacter_Enemy>(HitResult.Actor));
			}
		}
	}
	if(AttackedEnemyArray.Num()<Property.MaxAttackEnemyNum && DetectedTotalEnemy.Num()>0)
	{
		for (const auto& Enemy : DetectedTotalEnemy.Array())
		{
			if (AttackedEnemyArray.Num() >= Property.MaxAttackEnemyNum) break;
			if (Enemy)
			{
				AttackedEnemyArray.Add(Cast<ACharacter_Enemy>(Enemy));
			}
		}
	}
	if (AttackedEnemyArray.Num() > 0 && !isAttacking) Attack();
}

void AActor_Tower::Attack()
{
	if (AttackedEnemyArray.Num() == 0 || CanAttack == false) return;
	for(const auto& AttackedEnemy : AttackedEnemyArray.Array())
	{
		if(AttackedEnemy)
		{
			const FVector a = AttackedEnemy->GetActorLocation();
			const FVector b = GetActorLocation();
			const int dist = UKismetMathLibrary::VSize(a - b);
			if (dist <= Property.AttackRange && !AttackedEnemy->isDead)
			{
				FireBullet();
				isAttacking = true;
			}
			else
			{
					DetectedTotalEnemy.Remove(AttackedEnemy);
					IgnoreActors.Remove(AttackedEnemy);
					AttackedEnemyArray.Remove(AttackedEnemy);
					if (AttackedEnemyArray.Num() == 0) isAttacking=false;
			}
		}
	}
}

void AActor_Tower::ChangeMat()
{
	const int nG = MGun.Num();
	const int nR = MBase.Num();
	APlayerController_TowerDefence* Pc = Cast<APlayerController_TowerDefence>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (A) {
		A = !A;
		SetActorEnableCollision(false);
		Pc->bEnableClickEvents = 0;
		CanAttack = false;
		for (int i = 0; i < nG; i++) {
			myGun->SetMaterial(i, UnMat);
		}
		for (int i = 0; i < nR; i++) {
			Base->SetMaterial(i, UnMat);
		}
	}
	else {
		A = !A;
		CanAttack = true;
		isBuilt = true;
		SetActorEnableCollision(true);
		for (int i = 0; i < nG; i++) {
			myGun->SetMaterial(i, MGun[i]);
		}
		for (int i = 0; i < nR; i++) {
			Base->SetMaterial(i, MBase[i]);
		}
	}
}

void AActor_Tower::ForbidPut()
{
	const int nG = MGun.Num();
	const int nR = MBase.Num();
	for (int i = 0; i < nG; i++) {
		myGun->SetMaterial(i, ForbidPutMat);
	}
	for (int i = 0; i < nR; i++) {
		Base->SetMaterial(i, ForbidPutMat);
	}
}

void AActor_Tower::AllowPut()
{
	const int nG = MGun.Num();
	const int nR = MBase.Num();
	for (int i = 0; i < nG; i++) {
		myGun->SetMaterial(i, UnMat);
	}
	for (int i = 0; i < nR; i++) {
		Base->SetMaterial(i, UnMat);
	}
}

// Called when the game starts or when spawned
void AActor_Tower::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Actors;
	StartCheck();
	MBase = Base->GetMaterials();
	MGun = myGun->GetMaterials();
	A = true;
	CanAttack = false;
	isBuilt = false;
	isMaxLevel = false;
	Building_CurLevel = 1;
	BuildingCur_HP = Property.MaxHP;
}


float AActor_Tower::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float PhysicsHarmRelief = Property.PhysicalDefense / (602 + Property.PhysicalDefense);
	const int Damage = DamageAmount-(DamageAmount * PhysicsHarmRelief);
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

// Called every frame
void AActor_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackedEnemyArray.Num()>0) {
		if (!AttackedEnemyArray.Array()[0]->isDead && CanAttack)
		{
			const FVector a = GetActorLocation();
			const FVector b = AttackedEnemyArray.Array()[0]->GetActorLocation();
			const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(a, b);
			FRotator Rotation = FMath::RInterpTo(GetActorRotation(), LookRotation, DeltaTime, 10);
			myGun->SetWorldRotation(FRotator(0, LookRotation.Yaw, 0));
		}
	}
}

