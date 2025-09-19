// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstance.h"
#include "Wall.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = false;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BallMesh->SetupAttachment(GetRootComponent());

}

void ABall::BeginPlay()
{
	Super::BeginPlay();

}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::TakeHit()
{
	AWall* MyOwner = Cast<AWall>(GetOwner());
	if (!MyOwner) return;
	MyOwner->RemoveBallFromArray(this);
	Destroy();
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