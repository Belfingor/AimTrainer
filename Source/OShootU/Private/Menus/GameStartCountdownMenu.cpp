// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/GameStartCountdownMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGameStartCountdownMenu::Setup(bool ShowMouseCursor)
{
	Super::Setup(ShowMouseCursor);
	UGameplayStatics::SetGamePaused(this, true);
}

void UGameStartCountdownMenu::Teardown()
{
	Super::Teardown();
	UGameplayStatics::SetGamePaused(this, false);
}

void UGameStartCountdownMenu::Update(float DeltaTime)
{
	TimerLength -= DeltaTime;
	int32 DisplayTimerInSeconds = FMath::TruncToInt32(TimerLength + 1.f);
	if (TimerLength <= 0.f)
	{
		Teardown();
		return;
	}
	SetCountdownText(DisplayTimerInSeconds);
}

void UGameStartCountdownMenu::SetCountdownText(int32 Seconds)
{
	CountdownText->SetText(FText::FromString(FString::FromInt(Seconds)));
}
