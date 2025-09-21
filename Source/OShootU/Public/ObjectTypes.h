#pragma once

UENUM(BlueprintType)
enum class EBallColors : uint8
{
	EBC_Red UMETA(DisplayName = "Red"),
	EBC_Green UMETA(DisplayName = "Green"),
	EBC_Blue UMETA(DisplayName = "Blue") 
};

const TArray<FLinearColor> ArrBallColors
{ 
	FLinearColor::Red, 
	FLinearColor::Green, 
	FLinearColor::Blue 
};

const TMap<FLinearColor, EBallColors> ColorsMap = // this conversion is used so we can pass color values to AimOverlay as enums
{
	{ FLinearColor::Red, EBallColors::EBC_Red },
	{ FLinearColor::Green, EBallColors::EBC_Green },
	{ FLinearColor::Blue, EBallColors::EBC_Blue }
};