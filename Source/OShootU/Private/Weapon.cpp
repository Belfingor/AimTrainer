// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterPlayer.h"
#include "Ball.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	LineTraceParams.AddIgnoredActor(this);
	LineTraceParams.AddIgnoredActor(GetOwner());
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner)
{
	SetOwner(NewOwner);
	AttachMeshToSocket(InParent, InSocketName);
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	WeaponMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::Shoot()
{
	AShooterPlayer* MyOwner = Cast<AShooterPlayer>(GetOwner());
	if (!MyOwner) return;
	FVector StartLocation;
	FVector ForwardVector;
	MyOwner->GetCrosshairTrace(StartLocation, ForwardVector);
	FVector EndLocation = ForwardVector * 1000000.f;
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, LineTraceParams))
	{	
		ABall* DamagedBall = Cast<ABall>(Hit.GetActor());
		if (DamagedBall)
		{
			DamagedBall->TakeHit();
			DrawDebugPoint(GetWorld(), Hit.Location, 10.0f, FColor::Yellow, false, 3.0f);
		}
		else
		{
			MyOwner->ReducePLayerHealth(MissHealthPenalty);
			// Did hit something but not a Ball
		}
	}
	else
	{
		//Did not hit anything
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1.0f, 0, .5f);
	}
}

