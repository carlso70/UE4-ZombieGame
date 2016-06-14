// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ZombieInvasion.h"
#include "ZombieInvasionGameMode.h"
#include "ZombieInvasionHUD.h"
#include "Zombie.h"
#include "ZombieInvasionCharacter.h"
#include "Blueprint/UserWidget.h"

AZombieInvasionGameMode::AZombieInvasionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AZombieInvasionHUD::StaticClass();
	
}
