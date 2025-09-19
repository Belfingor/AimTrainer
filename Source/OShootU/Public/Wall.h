// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class ABall;
class AShooterPlayer;

UCLASS()
class OSHOOTU_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AWall();
	virtual void Tick(float DeltaTime) override;
	void CheckIfNeedResetBalls();
	void RemoveBallFromArray(ABall* BallToRemove);
	
protected:
	virtual void BeginPlay() override;
	
private:
	void SpawnBalls();
	AShooterPlayer* GetShooterPlayer();
	void ResettAllBallsOnWall();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallMesh;
	
	TArray<ABall*> BallsOnWall;

	UPROPERTY(EditAnywhere, Category = "Targets")
	TSubclassOf<ABall> BallClass;

	UPROPERTY(EditAnywhere, Category = "Targets")
	float EdgeOffset;

	UPROPERTY(EditAnywhere, Category = "Targets")
	int32 BallsNum;
};
