// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "PauseMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class OSHOOTU_API UPauseMenu : public UMenuBase
{
	GENERATED_BODY()
public:
	virtual void Setup() override;
	virtual void Teardown() override;
	UFUNCTION(BlueprintCallable)
	void MainMenuButtonPressed();

private:
	FName MainMenuMapName = TEXT("MainMenuMap");
};
