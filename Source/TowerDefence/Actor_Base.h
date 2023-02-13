// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Base.generated.h"

UCLASS()
class TOWERDEFENCE_API AActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Base();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainBody;
	UPROPERTY(VisibleAnywhere, Category = Gameing)
	class ATowerDefenceGameModeBase* GM;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		float Base_CurHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		bool isDestory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float Base_MaxHP;
	UFUNCTION()
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
