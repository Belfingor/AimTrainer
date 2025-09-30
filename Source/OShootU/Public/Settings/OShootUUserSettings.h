// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "OShootUUserSettings.generated.h"


UCLASS()
class OSHOOTU_API UOShootUUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	//--------------------------------Properties-----------------------------------
	UPROPERTY(Config)
	float MouseSensitivity = 0.5f;
	UPROPERTY(Config)
	int32 FPSCap = 60;
	UPROPERTY(Config)
	float MasterVolume = 0.5f;

	//----------------------------------Setters------------------------------------
	void SetMouseSensitivity(float NewSensitivity);
	void SetFPSCap(int32 NewFPS);
	void SetMasterVolume(float Volume);
	
	//----------------------------------Getters------------------------------------
	float GetMouseSensitivity() { return MouseSensitivity; }
	int32 GetFPSCap() { return FPSCap; }
	float GetMasterVolume() { return MasterVolume; }
	
};
