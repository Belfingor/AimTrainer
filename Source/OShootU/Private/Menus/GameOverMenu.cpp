// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/GameOverMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "GameSave/MySaveGame.h"


void UGameOverMenu::Setup(bool ShowMouseCursor)
{
	Super::Setup(ShowMouseCursor);
	UGameplayStatics::SetGamePaused(this, true);
}

void UGameOverMenu::Setup(int32 Score)
{
	Setup(true);
	SetPlayerScoreString(Score);

	GameSaveData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0));
	if (GameSaveData) 
	{
		SetPlayerRecordString(GameSaveData->PlayerScoreRecord);	
	}
}

void UGameOverMenu::Teardown()
{
	Super::Teardown();
	UGameplayStatics::SetGamePaused(this, false);
}

void UGameOverMenu::MainMenuButtonPressed()
{
	Teardown();
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}

void UGameOverMenu::RestartButtonPressed()
{
	Teardown();
	UGameplayStatics::OpenLevel(GetWorld(), PlayingMapName);
}

void UGameOverMenu::SetPlayerScoreString(int32 Score)
{
	ScoreText->SetText(FText::FromString(FString("Score: " + FString::FromInt(Score))));
}

void UGameOverMenu::SetPlayerRecordString(int32 Score)
{
	RecordText->SetText(FText::FromString(FString("Record: " + FString::FromInt(Score))));
}