// Fill out your copyright notice in the Description page of Project Settings.

#include "Wall.h"
#include "Components/StaticMeshComponent.h"
#include "Ball.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	WallMesh->SetupAttachment(GetRootComponent());
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	SpawnBalls();
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		int32 BallsLeft = BallsOnWall.Num();
		GEngine->AddOnScreenDebugMessage( 1, 5.0f, FColor::Red, FString::Printf(TEXT("Balls Left: %d"), BallsLeft));
	}
}

void AWall::RemoveBallFromArray(ABall* BallToRemove)
{
	BallsOnWall.Remove(BallToRemove);
}

void AWall::SpawnBalls()
{
	FVector Origin;
	FVector Extent;
	if (!WallMesh) return;
	UStaticMesh* StaticMesh = WallMesh->GetStaticMesh();
	if (!StaticMesh) return;
	FVector WallLocation = GetActorLocation();
	StaticMesh->GetBounds().GetBox().GetCenterAndExtents(Origin, Extent);

	UWorld* World = GetWorld();
	if (!World) return;
	float Y = WallLocation.Y + Extent.Y;
	int32 ColorToSet = 0;
	const int32 ColorsInArray = ArrBallColors.Num() - 1;
	for (int32 i = 0; i < BallsNum; i++)
	{
		float RandX = FMath::RandRange(WallLocation.X + Origin.X - Extent.X + EdgeOffset, WallLocation.X + Origin.X + Extent.X - EdgeOffset);
		float RandZ = FMath::RandRange(WallLocation.Z + Origin.Z - Extent.Z + EdgeOffset, WallLocation.Z + Origin.Z + Extent.Z - EdgeOffset);
		FVector SpawnLocation(RandX, Y, RandZ);
		ABall* SpawnedBall = World->SpawnActor<ABall>(BallClass, SpawnLocation, FRotator::ZeroRotator);
		SpawnedBall->SetOwner(this);


		SpawnedBall->SetBallColor(ArrBallColors[ColorToSet]);
		if (ColorToSet == ColorsInArray)
		{
			ColorToSet = 0;
		}
		else
		{
			ColorToSet += 1; 
		}


		BallsOnWall.Add(SpawnedBall);
	}
}