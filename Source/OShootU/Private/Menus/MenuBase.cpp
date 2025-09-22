// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MenuBase.h"
#include "GameFramework/PlayerController.h"

void UMenuBase::Setup()
{
	UWorld* World = GetWorld();
	if (!World) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
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