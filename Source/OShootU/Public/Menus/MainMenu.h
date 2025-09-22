// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class OSHOOTU_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartGameButtonPressed();
	UFUNCTION(BlueprintCallable)
	void ExitButtonPressed();

private:
	FName GameMapName = TEXT("PlayingMap");
};
