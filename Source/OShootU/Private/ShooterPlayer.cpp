// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayer.h"
#include "Weapon.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "HUD/AimHUD.h"
#include "HUD/AimOverlay.h"

AShooterPlayer::AShooterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SkeletalMesh);

}

void AShooterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon->Equip(SkeletalMesh, FName("WeaponSocket"), this);
		Weapon = DefaultWeapon;
	}
	InitOverlay();
}

void AShooterPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(-LookAxisValue.Y);
	}
}

void AShooterPlayer::Shoot(const FInputActionValue& Value)
{
	Weapon->Shoot();
}

void AShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayer::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AShooterPlayer::Shoot);

	}

}

void AShooterPlayer::InitOverlay()
{
	if (APlayerController* PlayerController = GetPlayerController())
	{
		AAimHUD* AimHUD = Cast<AAimHUD>(PlayerController->GetHUD());
		if (AimHUD)
		{
			AimOverlay = AimHUD->GetAimOverlay();
			if (AimOverlay)
			{
				AimOverlay->SetHealthText(3);
			}
		}
	}
}

APlayerController* AShooterPlayer::GetPlayerController()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	return PlayerController;
}

bool AShooterPlayer::GetCrosshairTrace(FVector& OutWorldLocation, FVector& OutWolrdDirection)
{
	if (APlayerController* PlayerController = GetPlayerController())
	{
		int32 ViewportSizeX;
		int32 ViewportSizeY;
		PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);


		FVector2D CrosshairScreenLocation(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
		PlayerController->DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, OutWorldLocation, OutWolrdDirection);

		return true;
	}	
	return false;
}
