// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_pathPoint.generated.h"

UCLASS()
class TOWERDEFENCE_API AActor_pathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_pathPoint();
	UPROPERTY(EditAnywhere, Category = "Gameing")
		class UStaticMeshComponent* pathPoint;
	UPROPERTY(EditAnywhere, Category = "Gameing")
		class AActor_pathPoint* NextPoint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
