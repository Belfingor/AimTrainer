// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AimOverlay.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class OSHOOTU_API UAimOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCrosshairColor();
	void SetHealthText(int32 Health);
	void SetScoreCountText(int32 Score);

private:
	UPROPERTY (meta = (BindWidget))
	TObjectPtr<UImage> Crosshair;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreCountText;

};
