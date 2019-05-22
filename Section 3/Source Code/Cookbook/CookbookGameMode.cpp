// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Cookbook.h"
#include "CookbookGameMode.h"
#include "CookbookHUD.h"
#include "CookbookCharacter.h"

ACookbookGameMode::ACookbookGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACookbookHUD::StaticClass();
}
