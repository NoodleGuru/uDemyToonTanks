// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"

// public
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || DistanceToPlayer() > FireRange) return;

	RotateTurret(PlayerPawn->GetActorLocation());
}

// protected
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// private
void APawnTurret::CheckFireCondition()
{
	// check if enemy exists && alive
	if (!PlayerPawn) return;
	if (DistanceToPlayer() <= FireRange)
	{
		Fire();
	}
	
}
float APawnTurret::DistanceToPlayer()
{
	if (!PlayerPawn) return 0.f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
}