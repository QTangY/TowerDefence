// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Base.h"
#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AActor_Base::AActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MainBody->SetupAttachment(GetRootComponent());
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/AsianTemple/Environment/Mesh/SM_Tree_Medium_01a.SM_Tree_Medium_01a'"));
	if (MeshAsset.Object) {
		MainBody->SetStaticMesh(MeshAsset.Object);
	}
}

float AActor_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Base_CurHP -= DamageAmount;
	GM = Cast<ATowerDefenceGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Base_CurHP > 0) {
		if (GM->isWin) {
			GM->GameOver();
		}
	}
	else {
		Base_CurHP = 0;
		GM->isFail = true;
		GM->GameOver();
	}
	return DamageAmount;
}

// Called when the game starts or when spawned
void AActor_Base::BeginPlay()
{
	Super::BeginPlay();
	Base_CurHP = Base_MaxHP;
}

// Called every frame
void AActor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

