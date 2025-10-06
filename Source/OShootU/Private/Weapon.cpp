// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "ShooterPlayer.h"
#include "Ball.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Settings/OShootUUserSettings.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
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
	CalculateLineTrace();
	PlayShootSound();
	SpawnMuzzleFlashEffect();
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitIgnoredActors();
	Settings = GetUserSettings();
}

void AWeapon::PlayShootSound()
{
	if (!ShootSound || !Settings) return;
	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, this->GetActorLocation(), Settings->GetMasterVolume());
}

void AWeapon::SpawnMuzzleFlashEffect()
{
	if (MuzzleFlashNiagaraSystem && WeaponMesh)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			MuzzleFlashNiagaraSystem,
			WeaponMesh, 
			"MuzzleFlashSocket",
			FVector::Zero(),
			FRotator::ZeroRotator, 
			EAttachLocation::SnapToTarget, 
			true
		);
	}
}

void AWeapon::InitIgnoredActors()
{
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	LineTraceParams.AddIgnoredActors(ActorsToIgnore);
}

TObjectPtr<UOShootUUserSettings> AWeapon::GetUserSettings() const
{
	return Cast<UOShootUUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void AWeapon::CalculateLineTrace()
{
	AShooterPlayer* MyOwner = Cast<AShooterPlayer>(GetOwner());
	if (!MyOwner) return;
	FVector StartLocation;
	FVector ForwardVector;
	MyOwner->GetCrosshairTrace(StartLocation, ForwardVector);
	FVector EndLocation = ForwardVector * LineTraceForwardVectorLength;
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, LineTraceParams))
	{
		ABall* DamagedBall = Cast<ABall>(Hit.GetActor());
		if (DamagedBall)
		{
			DamagedBall->TakeHit();
			//DrawDebugPoint(GetWorld(), Hit.Location, 10.0f, FColor::Yellow, false, 3.0f);
		}
		else
		{
			// Did hit something but not a Ball
		}
	}
	else
	{
		//Did not hit anything
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1.0f, 0, .5f);
	}
}

