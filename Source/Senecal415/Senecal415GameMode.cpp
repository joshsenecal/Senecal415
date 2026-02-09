// Copyright Epic Games, Inc. All Rights Reserved.

#include "Senecal415GameMode.h"
#include "Senecal415Character.h"
#include "UObject/ConstructorHelpers.h"

ASenecal415GameMode::ASenecal415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
