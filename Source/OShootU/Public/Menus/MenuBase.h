// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

class USoundBase;
class UOShootUUserSettings;

UCLASS()
class OSHOOTU_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void Setup(bool ShowMouseCursor);
	UFUNCTION(BlueprintCallable)
	virtual void Teardown();
	virtual void PlayButtonPressSound();

protected:
	FName MainMenuMapName = TEXT("MainMenuMap");
	FName PlayingMapName = TEXT("PlayingMap");
	TObjectPtr<UOShootUUserSettings> Settings;
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> ButtonSound;
};
