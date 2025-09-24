// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShooterPlayer.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class AWeapon;
class UAimOverlay; 
class UMenuBase;
class UPauseMenu;
class UGameOverMenu;
class UGameStartCountdownMenu;


UCLASS()
class OSHOOTU_API AShooterPlayer : public APawn
{
	GENERATED_BODY()

public:
	AShooterPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	int32 AddToPlayerScore(int32 ScoreToAdd);
	int32 AdjustPlayerHealth(int32 Amount);
	void ReduceActiveColorTimer();

protected:
	virtual void BeginPlay() override;

	//-------------------------------Input Maping----------------------------------
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShootAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PauseMenuAction;
	//-----------------------------CallBacks for Input-----------------------------
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void TogglePauseGame(const FInputActionValue& Value);
	//-----------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> Weapon;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float MouseSensitivityModifier = 1.f;
	float MouseSensitivityModifierRange;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMenuBase> PauseMenuClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMenuBase> GameOverMenuClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMenuBase> CountdownMenuClass;

private:
	void InitOverlay();
	APlayerController* GetPlayerController();
	void SetRandomActiveColor();
	void UpdateTimerBar();
	void InitGameOverMenu();
	void InitStartGameCountdownMenu();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY()
	TObjectPtr<UAimOverlay> AimOverlay;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FLinearColor ActiveColor;
	FTimerHandle ColorTimer;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float ActiveColorTime = 10.f;
	const float TimerReduceValue = 0.2f;
	const int32 ClearWallScore = 5;
	const int32 ClearWallHealthRegen = 3;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 PlayerScore = 0;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int32 PlayerHealth = 10;
	const int32 PlayerMaxHealth = 10;
	const int32 ExpiredTimerHealthPenalty = 2;
	bool bPassedInitialTimer = false;

	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenu;
	UPROPERTY()
	TObjectPtr<UGameOverMenu> GameOverMenu;
	UPROPERTY()
	TObjectPtr<UGameStartCountdownMenu> CountdownMenu;

public:
	int32 GetClearWallScore() { return ClearWallScore; }
	int32 GetClearWallHealthRegen() { return ClearWallHealthRegen; }
	bool GetCrosshairTrace(FVector& OutWorldLocation, FVector& OutWolrdDirection);
	FLinearColor GetActiveColor() { return ActiveColor; }
};
