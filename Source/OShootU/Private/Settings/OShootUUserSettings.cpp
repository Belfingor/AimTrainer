// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/OShootUUserSettings.h"

void UOShootUUserSettings::SetMouseSensitivity(float NewSensitivity) 
{ 
	MouseSensitivity = NewSensitivity;
	SaveConfig();
}

void UOShootUUserSettings::SetFPSCap(int32 NewFPS)
{
	SetFrameRateLimit(NewFPS);
	FPSCap = NewFPS;
	SaveConfig();
	ApplyNonResolutionSettings();
}

void UOShootUUserSettings::SetMasterVolume(float Volume)
{
	MasterVolume = Volume;
	SaveConfig();
}
