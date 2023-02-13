// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Player.h"
#include "PlayerController_TowerDefence.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACharacter_Player::ACharacter_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

