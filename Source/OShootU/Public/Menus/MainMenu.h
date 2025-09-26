// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "MainMenu.generated.h"

class UWidgetSwitcher;
class UBorder;

UCLASS()
class OSHOOTU_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartGameButtonPressed();
	UFUNCTION(BlueprintCallable)
	void ExitButtonPressed();
	UFUNCTION(BlueprintCallable)
	void SettingsButtonPressed();
	UFUNCTION(BlueprintCallable)
	void ReturnButtonPressed();

private:
	FName GameMapName = TEXT("PlayingMap");

	const int32 MainMenuWidgetIndex = 0;
	const int32 SettingsWidgetIndex = 1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetMenuSwitcher;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> MainMenu;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Settings;
};
