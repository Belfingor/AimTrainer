// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/AimOverlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ObjectTypes.h"

void UAimOverlay::SetCrosshairColor()
{
	//Do crosshair color logic here
}

void UAimOverlay::SetHealthText(int32 Health)
{
	//Will Set Text here
}

void UAimOverlay::SetScoreCountText(int32 Score)
{
	//Will Set Text here
}

void UAimOverlay::SetActiveColorText(EBallColors Color)
{
	switch (Color)
	{
	case EBallColors::EBC_Red:
		ActiveColorText->SetText(FText::FromString("Red"));
		break;
	case EBallColors::EBC_Green: 
		ActiveColorText->SetText(FText::FromString("Green"));
		break;
	case EBallColors::EBC_Blue:
		ActiveColorText->SetText(FText::FromString("Blue"));
		break;

	}
}
