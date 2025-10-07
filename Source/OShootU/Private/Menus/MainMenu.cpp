// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Slider.h"
#include "Settings/OShootUUserSettings.h"
#include "Components/ComboBoxString.h"

void UMainMenu::Setup(bool ShowMouseCursor)
{
	Super::Setup(ShowMouseCursor);
	Settings = GetGameUserSettings();
	if (Settings)
	{
		if (SensitivitySlider)
		{
			SensitivitySlider->SetValue(Settings->GetMouseSensitivity());
		}
		if (FPSDropDown)
		{
			FPSDropDown->SetSelectedOption(FString::FromInt(Settings->GetFPSCap()));
		}
		if (VolumeSlider)
		{
			VolumeSlider->SetValue(Settings->GetMasterVolume());
		}
	}
}

void UMainMenu::StartGameButtonPressed()
{
	Teardown();
	UGameplayStatics::OpenLevel(GetWorld(), GameMapName);
}

void UMainMenu::ExitButtonPressed()
{
	Super::PlayButtonPressSound();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, true);
		}
	}
}

void UMainMenu::SettingsButtonPressed()
{
	Super::PlayButtonPressSound();
	if (WidgetMenuSwitcher)
	{
		WidgetMenuSwitcher->SetActiveWidgetIndex(SettingsWidgetIndex);
	}
}

void UMainMenu::ReturnButtonPressed()
{
	Super::PlayButtonPressSound();
	if (WidgetMenuSwitcher)
	{
		WidgetMenuSwitcher->SetActiveWidgetIndex(MainMenuWidgetIndex);
	}
}

void UMainMenu::HowToPlayButtonPressed()
{
	Super::PlayButtonPressSound();
}

float UMainMenu::ApplySentitivitySettings()
{
	if (Settings && SensitivitySlider)
	{
		Settings->SetMouseSensitivity(SensitivitySlider->GetValue());
		return Settings->GetMouseSensitivity();
	}
	return 0.f;
}

void UMainMenu::ApplyFPSChangeSettings(FString DropDownSelection)
{
	int32 FPSToSet = FCString::Atoi(*DropDownSelection);
	Settings->SetFPSCap(FPSToSet);
}

float UMainMenu::ApplyMasterVolume()
{
	if (Settings && VolumeSlider)
	{
		Settings->SetMasterVolume(VolumeSlider->GetValue());
		return Settings->GetMasterVolume();
	}
	return 0.f;
}

TObjectPtr<UOShootUUserSettings> UMainMenu::GetGameUserSettings() const 
{ 
	return Cast<UOShootUUserSettings>(UGameUserSettings::GetGameUserSettings()); 
}
