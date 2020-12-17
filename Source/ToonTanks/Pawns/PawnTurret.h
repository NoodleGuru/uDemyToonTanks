// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	float FireRange = 100.f;
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;

	void CheckFireCondition();	
	float DistanceToPlayer();
	

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
