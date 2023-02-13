// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Actor_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor_birthPoint.h"
#include "AIController_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PlayerController_TowerDefence.h"
#include "Actor_Tower.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
ACharacter_Enemy::ACharacter_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.	
	PrimaryActorTick.bCanEverTick = true;
	EnemyController = Cast<AAIController_Enemy>(GetController());
	this->FindComponentByClass<UCapsuleComponent>()->SetWorldScale3D(FVector(5,5,5));
	//Make AI rotate smoothly(avoid snapping)
	bUseControllerRotationYaw = false; //prepare for orient rotation to movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	constexpr float YawRotateRate = 360.0f;
	GetCharacterMovement()->RotationRate = FRotator(0, 0,YawRotateRate);
}

void ACharacter_Enemy::ArriveEnd()
{
 		UGameplayStatics::ApplyDamage(GM->AlineBase, Property.ArriveEndDamage, nullptr,this, nullptr);
		Death();
}

void ACharacter_Enemy::Death()
{
	GM = Cast<ATowerDefenceGameModeBase>(UGameplayStatics::GetGameMode(this));
	GM->SceneEnemyNumbers--;
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("当前敌人总数:%d"), GM->SceneEnemyNumbers));
	if (GM->EnemyisSpawned) 
	{
		GM->VictoryConditions();
		GM->GameOver();
	}
	if (EnemyController)
	{
		EnemyController->StopMovement();
	}
	onDie();
	GM->AddMoney(Value);
}

void ACharacter_Enemy::HitResult()
{
	if (AttackTower) 
	{
		UGameplayStatics::ApplyDamage(AttackTower, Property.PhysicalAttackValue, nullptr, this, DamageTypeClass);
	}
}

void ACharacter_Enemy::SetFaceToTarget(AActor* Target, float DeltaTime)
{
	const FVector a = GetActorLocation();
	const FVector b = Target->GetActorLocation();
	const FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(a, b);
	const FRotator Rotation = FMath::RInterpTo(GetActorRotation(), LookRotation, DeltaTime, 10);
	SetActorRotation(FRotator(0, Rotation.Yaw, 0));
}

void ACharacter_Enemy::StartDetection()
{
	GetWorldTimerManager().SetTimer(TowerDetectTimer, this, &ACharacter_Enemy::Detection, Enemy_DetectInterval, true);
	IgnoreDeleteActors.Empty();
	IgnoreAttackActors.Empty();
	attackOverlappingActors.Empty();
	deleteOverlappingActors.Empty();
	TargetRole = nullptr;
	AttackTower = nullptr;
}


void ACharacter_Enemy::Detection()
{
	FVector Start = GetActorLocation();
	FVector End = Start + 10;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);
	TArray<FHitResult> DetectionHitResults;
	TArray<FHitResult> AttackHitResults;
	bool bDetectionIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, Enemy_DetectRange, ObjectTypes, false, IgnoreDeleteActors.Array(), EDrawDebugTrace::None, DetectionHitResults, true);
	bool bAttackIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, Property.Enemy_AttackDistance, ObjectTypes, false, IgnoreAttackActors.Array(), EDrawDebugTrace::None, AttackHitResults, true);
	if (bAttackIsHit) 
	{
		for (auto Hit : AttackHitResults) 
		{
			AActor_Building* T = Cast<AActor_Building>(Hit.Actor);
			attackOverlappingActors.Add(T);
			IgnoreAttackActors.Add(T);
		}
	}
	else
	{
		if (bDetectionIsHit)
		{
			for (auto Hit : DetectionHitResults) 
			{
				AActor_Building* T = Cast<AActor_Building>(Hit.Actor);
				deleteOverlappingActors.Add(T);
				IgnoreDeleteActors.Add(T);
			}
		}
		else 
		{
			if (TargetRole == nullptr && AttackTower ==nullptr)
			{
				if (MoveStatus != EMoveStatus::MS_Attacking) 
				{
					MoveStatus = EMoveStatus::MS_MoveToBase;
					MoveToBase();
				}
			}
		}
	}
	Action();
}

void ACharacter_Enemy::Action()
{
	if (AttackTower != nullptr && AttackTower->isDestory)
	{
		attackOverlappingActors.Remove(AttackTower);
		IgnoreAttackActors.Remove(AttackTower);
		deleteOverlappingActors.Remove(AttackTower);
		IgnoreDeleteActors.Remove(AttackTower);
		TargetRole = nullptr;
		AttackTower = nullptr;
	}
	if (TargetRole != nullptr && TargetRole->isDestory)
	{
		deleteOverlappingActors.Remove(TargetRole);
		IgnoreDeleteActors.Remove(TargetRole);
		TargetRole = nullptr;
	}
	if (attackOverlappingActors.Num() > 0 && AttackTower == nullptr)
	{
		srand(time(nullptr));
		int index = rand() % attackOverlappingActors.Num();
		AttackTower = Cast<AActor_Building>(attackOverlappingActors.Array()[index]);
		if (AttackTower)
		{
			SetFaceToTarget(AttackTower, 0.25f);
			MoveStatus = EMoveStatus::MS_Attacking;
			if (EnemyController)
			{
				EnemyController->StopMovement();
			}
		}
	}
	else
	{
		if (deleteOverlappingActors.Num() > 0)
		{
			if (TargetRole)
			{
				if (MoveStatus != EMoveStatus::MS_Attacking)
				{
					MoveStatus = EMoveStatus::MS_MoveToTarget;
					MoveToTarget();
				}
			}
			else
			{
				srand(time(nullptr));
				const int index = rand() % deleteOverlappingActors.Num();
				TargetRole = Cast<AActor_Building>(deleteOverlappingActors.Array()[index]);
				if (TargetRole)
				{
					if (MoveStatus != EMoveStatus::MS_Attacking)
					{
						MoveStatus = EMoveStatus::MS_MoveToTarget;
						MoveToTarget();
					}
				}
			}
		}
	}
}

void ACharacter_Enemy::MoveToTarget()
{
	if (TargetRole)
	{
		if (EnemyController) 
		{
			isAttacking = false;
			EnemyController->MoveToActor(TargetRole,5.0,false);
		}
	}
	else 
	{
		StartDetection();
	}
}

void ACharacter_Enemy::MoveToBase()
{
	if (GM->AlineBase && EnemyController)
	{
		isAttacking = false;
		EnemyController->MoveToActor(GM->AlineBase, 5.0, false);
	}
}

float ACharacter_Enemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float PhysicalHarmRelief = Property.PhysicalDefense / (Property.PhysicalDefense + 602);
	const int Damage = DamageAmount-DamageAmount * PhysicalHarmRelief;
	if (CurHP > Damage) 
	{
		CurHP -= Damage;
	}
	else 
	{
		CurHP = 0;
		isDead = true;
		Death();
	}
	return Damage;
}

// Called when the game starts or when spawned
void ACharacter_Enemy::BeginPlay()
{
	Super::BeginPlay();
	isDead = false;
	isAttacking = false;
	CurHP = Property.MaxHP;
	GM = Cast<ATowerDefenceGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	EnemyController = Cast<AAIController>(this->GetController());
	MainPlayerController = Cast<APlayerController_TowerDefence>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ACharacter_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static bool doOnce = true;
	if (GM->AlineBase->IsOverlappingActor(this)&&doOnce)
	{
		doOnce = false;
		ArriveEnd();
	}
}

// Called to bind functionality to input
void ACharacter_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

