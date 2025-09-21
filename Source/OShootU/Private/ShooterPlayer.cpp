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
#include "Math/UnrealMathUtility.h"
#include "ObjectTypes.h"

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

	MouseSensitivityModifierRange = FMath::Clamp(MouseSensitivityModifier, 0.1f, 1.f);
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

	SetRandomActiveColor();
}

void AShooterPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X * MouseSensitivityModifier);
		AddControllerPitchInput(-LookAxisValue.Y * MouseSensitivityModifier);
	}
}

void AShooterPlayer::Shoot(const FInputActionValue& Value)
{
	Weapon->Shoot();
}

void AShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TimeTimeRemaining = GetWorldTimerManager().GetTimerRemaining(ColorTimer);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Timer remaining: %f"), TimeTimeRemaining));
	}
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

void AShooterPlayer::SetRandomActiveColor()
{
	TArray<FLinearColor> AvailableColors;
	for (auto color : ArrBallColors)
	{
		if (color != ActiveColor)
		{
			AvailableColors.AddUnique(color);
		}
	}

	int32 Selection = FMath::RandRange(0, AvailableColors.Num() - 1);
	ActiveColor = AvailableColors[Selection];
	AimOverlay->SetActiveColorText(ColorsMap[ActiveColor]);

	GetWorldTimerManager().SetTimer(ColorTimer, this, &AShooterPlayer::SetRandomActiveColor, ActiveColorTime);
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
