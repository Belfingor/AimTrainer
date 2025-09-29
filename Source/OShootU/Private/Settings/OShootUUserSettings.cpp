// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/OShootUUserSettings.h"

void UOShootUUserSettings::SetMouseSensitivity(float NewSensitivity) 
{ 
	MouseSensitivity = NewSensitivity;
}

void UOShootUUserSettings::SetFPSCap(int32 NewFPS)
{
	FPSCap = NewFPS;
}
