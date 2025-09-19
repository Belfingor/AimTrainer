// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UStaticMeshComponent;
class AShooterPlayer;

UCLASS()
class OSHOOTU_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();
	virtual void Tick(float DeltaTime) override;
	void TakeHit();
	void RemoveBallFromWall();

protected:
	virtual void BeginPlay() override;

private:
	AShooterPlayer* GetShooterPlayer();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BallMesh;

	FLinearColor BallColor;

public: //Setters and Getters
	void SetBallColor(FLinearColor Color);
	FLinearColor GetBallColor() { return BallColor; }
};
