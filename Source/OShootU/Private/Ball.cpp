// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Wall.h"
#include "ShooterPlayer.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = false;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	RootComponent = BallMesh;

}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::TakeHit()
{
	AShooterPlayer* Player = GetShooterPlayer();
	if (Player)
	{
		if (Player->GetActiveColor() == GetBallColor())
		{
			RemoveBallFromWall();
			Player->AddToPlayerScore(BallScoreValue);
		}
		else
		{
			Player->AdjustPlayerHealth(-WrongBallHealthPenalty);
		}
	}
}

void ABall::RemoveBallFromWall()
{
	AWall* MyOwner = Cast<AWall>(GetOwner());
	if (!MyOwner) return;
	MyOwner->RemoveBallFromArray(this);
	Destroy();
	MyOwner->CheckIfNeedResetBalls();
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

}

AShooterPlayer* ABall::GetShooterPlayer()
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return nullptr;
	AShooterPlayer* Player = Cast<AShooterPlayer>(PlayerController->GetPawn());

	return Player;
}

void ABall::SetBallColor(FLinearColor Color)
{
	UMaterialInterface* BaseMaterial = BallMesh->GetMaterial(0);
	UMaterialInstanceDynamic* DynamicMaterialInstance = BallMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BaseMaterial);
	if (DynamicMaterialInstance)
	{
		DynamicMaterialInstance->SetVectorParameterValue(FName("ColorParam"), Color);
		BallColor = Color;
	}
}