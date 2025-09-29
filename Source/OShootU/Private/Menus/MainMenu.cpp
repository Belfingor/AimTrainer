// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Slider.h"
#include "Settings/OShootUUserSettings.h"

void UMainMenu::StartGameButtonPressed()
{
	Teardown();
	UGameplayStatics::OpenLevel(GetWorld(), GameMapName);

}
void UMainMenu::ExitButtonPressed()
{
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
	if (WidgetMenuSwitcher)
	{
		WidgetMenuSwitcher->SetActiveWidgetIndex(SettingsWidgetIndex);
	}
}

void UMainMenu::ReturnButtonPressed()
{
	if (WidgetMenuSwitcher)
	{
		WidgetMenuSwitcher->SetActiveWidgetIndex(MainMenuWidgetIndex);
	}
}

float UMainMenu::ApplySentitivitySettings()
{
	TObjectPtr<UOShootUUserSettings> Settings = GetGameUserSettings();
	if (Settings)
	{
		Settings->SetMouseSensitivity(SensitivitySlider->GetValue());
		return Settings->GetMouseSensitivity();
	}
	return 0.f;
}

TObjectPtr<UOShootUUserSettings> UMainMenu::GetGameUserSettings() const { return Cast<UOShootUUserSettings>(UGameUserSettings::GetGameUserSettings()); }
