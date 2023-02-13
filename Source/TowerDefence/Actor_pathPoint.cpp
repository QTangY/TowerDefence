// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_pathPoint.h"

// Sets default values
AActor_pathPoint::AActor_pathPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pathPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	auto MeshMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (MeshAsset.Object && MeshMaterial.Object) {
		pathPoint->SetStaticMesh(MeshAsset.Object);
		pathPoint->SetMaterial(0, MeshMaterial.Object);
	}
	this->SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AActor_pathPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_pathPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

