// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_birthPoint.h"
#include "TowerDefenceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Actor_pathPoint.h"
#include "Character_Enemy.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AActor_birthPoint::AActor_birthPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	birthPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	auto MeshMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (MeshAsset.Object && MeshMaterial.Object) {
		birthPoint->SetStaticMesh(MeshAsset.Object);
		birthPoint->SetMaterial(0, MeshMaterial.Object);
	}
	this->SetActorHiddenInGame(true);
}

void AActor_birthPoint::EnemySpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GM = Cast<ATowerDefenceGameModeBase>(UGameplayStatics::GetGameMode(this));
	int Leveldiff = thisLevelDifficulty- 1;
	if (!GM->EnemyisSpawned) 
	{
		FVector Location = GetActorLocation();
		XR= 1000;
		YR = 1000;
		FVector offest = FVector(rand()%(2* XR)- XR, rand()%(2* YR) - YR,0);
		FRotator Rotation = GetActorRotation();
		if (EnemyTypeAndNums[EnemyCurWaveNums].Numbers>0&&EnemyTypeAndNums[EnemyCurWaveNums].EnemyType!=nullptr)
		{
			FActorSpawnParameters ActorParmas;
			ActorParmas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			if (!GM->isFail) {
				GetWorld()->SpawnActor<ACharacter_Enemy>(EnemyTypeAndNums[EnemyCurWaveNums].EnemyType, Location+offest, Rotation, ActorParmas);
			}
			EnemyCurNums++;
			GM->SceneEnemyNumbers++;

		}
		int EnemyNums = (EnemyTypeAndNums[EnemyCurWaveNums].Numbers / 2) * Leveldiff + EnemyTypeAndNums[EnemyCurWaveNums].Numbers;
		if (EnemyCurNums >= EnemyNums&& EnemyCurNums!=0)
		{
			EnemyCurNums = 0;
			EnemyCurWaveNums++;
			FString path = "WidgetBlueprint'/Game/Game/BulePrint/UI/LastWave_UI.LastWave_UI_C'";
			UClass* widgetClass = LoadClass<UUserWidget>(nullptr, path.GetCharArray().GetData());
			UUserWidget* userWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
			if (userWidget&& EnemyCurWaveNums == EnemyTypeAndNums.Num() - 1) 
			{
				userWidget->AddToViewport();
			}
			if (EnemyCurWaveNums >= EnemyTypeAndNums.Num()) 
			{
				GM->EnemyisSpawned = true;
			}
			else 
			{
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AActor_birthPoint::EnemySpawn, EnemyWaveSpawnIntervalTime, true);
			}
		}
		else 
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AActor_birthPoint::EnemySpawn, EnemySpawnIntervalTime, true);
		}
	}
}

// Called when the game starts or when spawned
void AActor_birthPoint::BeginPlay()
{
	Super::BeginPlay();
	EnemyCurWaveNums = 0;
	EnemyCurNums=0;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AActor_birthPoint::EnemySpawn, 2.0f, true);
}

// Called every frame
void AActor_birthPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

