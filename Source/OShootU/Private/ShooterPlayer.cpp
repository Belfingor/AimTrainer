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
#include "Menus/PauseMenu.h"
#include "Menus/GameOverMenu.h"
#include "Menus/GameStartCountdownMenu.h"

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
	//Decided to init countdown after first tick as player's camera was not initialized properly otherwise
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AShooterPlayer::InitStartGameCountdownMenu);
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

void AShooterPlayer::TogglePauseGame(const FInputActionValue& Value)
{
	APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;
	
	PauseMenu = CreateWidget<UPauseMenu>(PlayerController, PauseMenuClass);
	PauseMenu->AddToViewport();
	if (PauseMenu)
	{
		PauseMenu->Setup(true);
		PauseMenu = nullptr; //Not sure yet if I want to set it to nullptr that early, but works good for now
	}
}

void AShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTimerBar();
}

void AShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayer::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AShooterPlayer::Shoot);
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Triggered, this, &AShooterPlayer::TogglePauseGame);
	}
}

int32 AShooterPlayer::SetPlayerScore(int32 ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
	AimOverlay->SetScoreCountText(PlayerScore);
	return PlayerScore;
}

int32 AShooterPlayer::ReducePLayerHealth(int32 HealthToDeduct)
{
	PlayerHealth -= HealthToDeduct;
	AimOverlay->SetHealthText(PlayerHealth);
	if (PlayerHealth <= 0)
	{
		InitGameOverMenu();
	}
	return PlayerHealth;
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
				AimOverlay->SetHealthText(PlayerHealth);
				AimOverlay->SetScoreCountText(PlayerScore);
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
	if (AimOverlay)
	{
		AimOverlay->SetActiveColorText(ColorsMap[ActiveColor]);
	}
	
	GetWorldTimerManager().SetTimer(ColorTimer, this, &AShooterPlayer::SetRandomActiveColor, ActiveColorTime);
}

void AShooterPlayer::UpdateTimerBar()
{
	float TimeRemaining = GetWorldTimerManager().GetTimerRemaining(ColorTimer);
	float TimePercent = TimeRemaining / ActiveColorTime;
	if (AimOverlay)
	{
		AimOverlay->SetTimeBarPercent(TimePercent);
	}
}

void AShooterPlayer::InitGameOverMenu()
{
	APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	GameOverMenu = CreateWidget<UGameOverMenu>(PlayerController, GameOverMenuClass);
	GameOverMenu->AddToViewport();
	if (GameOverMenu)
	{
		GameOverMenu->Setup(PlayerScore);
	}
}

void AShooterPlayer::InitStartGameCountdownMenu()
{
	APlayerController* PlayerController = GetPlayerController();
	if (!PlayerController) return;

	CountdownMenu = CreateWidget<UGameStartCountdownMenu>(PlayerController, CountdownMenuClass);
	CountdownMenu->AddToViewport();
	if (CountdownMenu)
	{
		CountdownMenu->Setup(false);
	}
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
