// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PGSPlayerController.generated.h"

class APGSCharacter;
/**
 * 
 */
UCLASS()
class PGS_API APGSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APGSPlayerController();
	
protected:
	APGSCharacter * PlayerCharacter;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchCamera(float Value);
	void YawCamera(float Value);
	void JumpAction();
	void LightAttackAction();
	void SprintAction();
	void StopSprintAction();
	void LockCameraAction();
	void UnlockCameraAction();
};
