// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Building.generated.h"

UCLASS()
class TOWERDEFENCE_API AActor_Building : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_Building();
	bool A;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		class UStaticMeshComponent* Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		class UWidgetComponent*W_HP;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		class UWidgetComponent* W_BuildingBar;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		class UChildActorComponent* C_Chassis;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPaperSpriteComponent* C_PaperSprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* Collsion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		int UpGradeMoney;//建筑升级所需金钱
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		int Building_MaxLavel;//建筑最大等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		int SellPrice;//建筑出售金钱
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		UMaterialInterface* UnMat;//未放置时的材质
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerSetting")
		UMaterialInterface* ForbidPutMat;//不可放置时的材质
	UPROPERTY(EditAnywhere, Category = "TowerSetting")
		TArray<USkeletalMesh*> DiffLevelMesh;//不同等级时的形态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gaming")
		float BuildingCur_HP;//建筑当前血量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gaming")
		int Building_CurLevel;//建筑当前等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		bool isMaxLevel;//是否达到最高等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		bool isDestory;//是否被销毁
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameing")
		bool isBuilt;//是否建造完成
	UFUNCTION(BlueprintCallable)
	virtual void upGrade();
	UFUNCTION(BlueprintCallable)
	virtual void ChangeMat();
	UFUNCTION(BlueprintCallable)
	virtual void ForbidPut();
	UFUNCTION(BlueprintCallable)
	virtual void AllowPut();
};
