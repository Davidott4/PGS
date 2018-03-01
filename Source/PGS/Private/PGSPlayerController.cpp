// Fill out your copyright notice in the Description page of Project Settings.

#include "PGSPlayerController.h"
#include "PGSCharacter.h"




APGSPlayerController::APGSPlayerController()
{
	
}

void APGSPlayerController::BeginPlay()
{
	PlayerCharacter = Cast<APGSCharacter>(GetPawn());
	
	if (PlayerCharacter != NULL)
	{
		this->Possess(PlayerCharacter);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PLAYERCONTROLLER FAILED TO POSESS PLAYERCHARACTER"));
	}
}

void APGSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForwardAxis", this, &APGSPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRightAxis", this,  &APGSPlayerController::MoveRight);
		InputComponent->BindAxis("LookUpAxis", this, &APGSPlayerController::PitchCamera);
		InputComponent->BindAxis("LookRightAxis", this,  &APGSPlayerController::YawCamera);
	}
}

void APGSPlayerController::MoveForward(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->MoveForward(Value);
	}
}

void APGSPlayerController::MoveRight(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->MoveRight(Value);
	}
}

void APGSPlayerController::PitchCamera(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->PitchCamera(Value);
	}
}

void APGSPlayerController::YawCamera(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->YawCamera(Value);
	}
}
