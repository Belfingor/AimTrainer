// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/AimOverlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "ObjectTypes.h"

void UAimOverlay::SetCrosshairColor()
{
	//Do crosshair color logic here
}

void UAimOverlay::SetHealthText(int32 Health)
{
	HealthText->SetText(FText::FromString(FString::FromInt(Health)));
}

void UAimOverlay::SetScoreCountText(int32 Score)
{
	ScoreCountText->SetText(FText::FromString(FString::FromInt(Score)));
}

void UAimOverlay::SetActiveColorText(EBallColors Color)
{
	switch (Color)
	{
	case EBallColors::EBC_Red:
		ActiveColorText->SetText(FText::FromString("Red"));
		ActiveColorText->SetColorAndOpacity(FLinearColor::Red);
		break;
	case EBallColors::EBC_Green: 
		ActiveColorText->SetText(FText::FromString("Green"));
		ActiveColorText->SetColorAndOpacity(FLinearColor::Green);
		break;
	case EBallColors::EBC_Blue:
		ActiveColorText->SetText(FText::FromString("Blue"));
		ActiveColorText->SetColorAndOpacity(FLinearColor::Blue);
		break;

	}
}

void UAimOverlay::SetTimeBarPercent(float Percent)
{
	TimeBarFiller->SetPercent(Percent);
}
