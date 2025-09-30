// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class UStaticMeshComponent;
class USoundBase;
class UNiagaraSystem;
class UOShootUUserSettings;


UCLASS()
class OSHOOTU_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner);
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	void Shoot();

protected:
	virtual void BeginPlay() override;

	
private:
	void PlayShootSound();
	void SpawnMuzzleFlashEffect();
	TObjectPtr<UOShootUUserSettings> GetUserSettings() const;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> ShootSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UNiagaraSystem> MuzzleFlashNiagaraSystem;

	TObjectPtr<UOShootUUserSettings> Settings;

	FCollisionQueryParams LineTraceParams;

};
