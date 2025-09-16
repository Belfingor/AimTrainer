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


UCLASS()
class OSHOOTU_API AShooterPlayer : public APawn
{
	GENERATED_BODY()

public:
	AShooterPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	//-------------------------------Input Maping----------------------------------
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShootAction;
	//-----------------------------CallBacks for Input-----------------------------
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	//-----------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> Weapon;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;

public:
	FVector GetCameraForwardVector();
	FVector GetCameraLocation();
};
