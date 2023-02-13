// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor_Building.h"
#include "Actor_Wall.generated.h"

USTRUCT(BlueprintType)
struct FWall_Property
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float PhysicsDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float MagicDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float MaxHP;
};
/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API AActor_Wall : public AActor_Building
{
	GENERATED_BODY()
	AActor_Wall();
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Setting)
	FWall_Property Property;
	UPROPERTY(EditAnywhere,Category=Mesh)
	class UStaticMeshComponent* Wall;
	UPROPERTY(VisibleAnywhere, Category = "Gameing")
		TArray<UMaterialInterface*> M_Wall;
	virtual void upGrade()override ;
	virtual void ChangeMat() override;
	virtual void ForbidPut()override;
	virtual void AllowPut() override;
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
