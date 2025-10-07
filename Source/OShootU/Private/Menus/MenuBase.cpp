// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MenuBase.h"
#include "GameFramework/PlayerController.h"
#include "Settings/OShootUUserSettings.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

void UMenuBase::Setup(bool ShowMouseCursor)
{
	UWorld* World = GetWorld();
	if (!World) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = ShowMouseCursor;

	Settings = Cast<UOShootUUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void UMenuBase::Teardown()
{
	RemoveFromParent();

	UWorld* World = GetWorld();
	if (!World) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}

void UMenuBase::PlayButtonPressSound()
{
	if (!ButtonSound || !Settings) return;
	UGameplayStatics::PlaySound2D(this, ButtonSound, Settings->GetMasterVolume());
}
