// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menus/MenuBase.h"
#include "GameStartCountdownMenu.generated.h"

class UTextBlock;

UCLASS()
class OSHOOTU_API UGameStartCountdownMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	virtual void Setup(bool ShowMouseCursor) override;
	virtual void Teardown() override;
	UFUNCTION(BlueprintCallable)
	void Update(float DeltaTime);

private:
	void SetCountdownText(int32 Seconds);
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountdownText;
	float TimerLength = 3.f;
};
