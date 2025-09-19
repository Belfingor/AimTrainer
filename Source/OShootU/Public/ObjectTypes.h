#pragma once

UENUM(BlueprintType)
enum class EBallColors : uint8 //Currently unused. May not need it at the end
{
	EBC_Red UMETA(DisplayName = "Red"),
	EBC_Green UMETA(DisplayName = "Green"),
	EBC_Blue UMETA(DisplayName = "Blue") 
};

const TArray<FLinearColor> ArrBallColors{ FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue };