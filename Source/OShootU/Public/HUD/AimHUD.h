// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AimHUD.generated.h"

/**
 * 
 */
UCLASS()
class OSHOOTU_API AAimHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
	TSubclassOf<class UAimOverlay> AimOverlayClass;

	UPROPERTY()
	TObjectPtr<UAimOverlay> AimOverlay;
	
public:
	FORCEINLINE UAimOverlay* GetAimOverlay() const { return AimOverlay; }
};
