// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterPlayer.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
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

	FVector ForwardVector = MyOwner->GetCameraForwardVector();
	FVector StartLocation = MyOwner->GetCameraLocation();


	DrawDebugLine(GetWorld(), StartLocation, ForwardVector * 10000.f, FColor::Red, false, 1.0f, 0, .1f);

}

