// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/AimHUD.h"
#include "HUD/AimOverlay.h"

void AAimHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;
	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller || !AimOverlayClass) return;

	AimOverlay = CreateWidget<UAimOverlay>(Controller, AimOverlayClass);
	AimOverlay->AddToViewport();
}
