// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}
// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalcMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalcRotInput);
	PlayerInputComponent->BindAxis("Camera Distance", this, &APawnTank::CameraDist);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalcMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalcRotInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::CameraDist(float Value)
{
	float SpringArmLength = SpringArm->TargetArmLength - (Value * 10.f);
	SpringArm->TargetArmLength = FMath::Clamp(SpringArmLength, 200.f, 1000.f);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
}