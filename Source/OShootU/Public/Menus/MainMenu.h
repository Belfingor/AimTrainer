// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "MainMenu.generated.h"

class UOShootUUserSettings;
class UWidgetSwitcher;
class UBorder;
class USlider;
class UComboBoxString;

UCLASS()
class OSHOOTU_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	virtual void Setup(bool ShowMouseCursor) override;
	UFUNCTION(BlueprintCallable)
	void StartGameButtonPressed();
	UFUNCTION(BlueprintCallable)
	void ExitButtonPressed();
	UFUNCTION(BlueprintCallable)
	void SettingsButtonPressed();
	UFUNCTION(BlueprintCallable)
	void ReturnButtonPressed();
	UFUNCTION(BlueprintCallable)
	void HowToPlayButtonPressed();

	//----------------------------------Settings-----------------------------------
	UFUNCTION(BlueprintCallable)
	float ApplySentitivitySettings();
	UFUNCTION(BlueprintCallable)
	void ApplyFPSChangeSettings(FString DropDownSelection);
	UFUNCTION(BlueprintCallable)
	float ApplyMasterVolume();

private:
	TObjectPtr<UOShootUUserSettings> GetGameUserSettings() const;
	TObjectPtr<UOShootUUserSettings> Settings;

	FName GameMapName = TEXT("PlayingMap");

	const int32 MainMenuWidgetIndex = 0;
	const int32 SettingsWidgetIndex = 1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetMenuSwitcher;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> MainMenu;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> SettingsMenu;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> SensitivitySlider;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> VolumeSlider;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> FPSDropDown;
};
