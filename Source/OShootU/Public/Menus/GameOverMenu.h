// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "GameOverMenu.generated.h"

class UMySaveGame;
class UTextBlock;

UCLASS()
class OSHOOTU_API UGameOverMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	virtual void Setup(bool ShowMouseCursor) override;
	void Setup(int32 Score);
	virtual void Teardown() override;
	UFUNCTION(BlueprintCallable)
	void MainMenuButtonPressed();
	UFUNCTION(BlueprintCallable)
	void RestartButtonPressed();

private:
	void SetPlayerScoreString(int32 Score);
	void SetPlayerRecordString(int32 Score);
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RecordText;
	TObjectPtr<UMySaveGame> GameSaveData;
};
