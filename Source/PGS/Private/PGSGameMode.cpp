// Fill out your copyright notice in the Description page of Project Settings.

#include "PGSGameMode.h"
#include "PGSPlayerController.h"
#include "PGSCharacter.h"

APGSGameMode::APGSGameMode()
{

	//tell your custom game mode to use your custom player controller
	PlayerControllerClass = APGSPlayerController::StaticClass();

	//you can set whatever (if any) other default framework classes
	//you wish for this game mode as well
	DefaultPawnClass = APGSCharacter::StaticClass();
	//GameStateClass = ACustomGameState::StaticClass();
	//HUDClass = ACustomGameHUD::StaticClass();
	//ReplaySpectatorPlayerControllerClass = ACustomReplaySpectatorPlayerController::StaticClass();
	//SpectatorClass = ACustomSpectatorClass::StaticClass();

}



