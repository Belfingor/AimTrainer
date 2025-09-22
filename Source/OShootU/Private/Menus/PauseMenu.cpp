// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::Setup()
{
	Super::Setup();
	UGameplayStatics::SetGamePaused(this, true);
}

void UPauseMenu::Teardown()
{
	Super::Teardown();
	UGameplayStatics::SetGamePaused(this, false);
}
