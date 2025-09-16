// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;

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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
};
