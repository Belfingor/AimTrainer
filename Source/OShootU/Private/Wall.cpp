// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/StaticMeshComponent.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	WallMesh->SetupAttachment(GetRootComponent());
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

