// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PGSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PGS_API APGSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APGSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetAnimationVariables();


	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float MinCameraPitch;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float MaxCameraPitch;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float CameraSpeed;

	// movement variables
	float ForwardInput;
	float RightInput;
	float CameraPitch;
	float CameraYaw;

	//animated variables
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		float RunVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FRotator LeanDelta;

	void MoveCharacter();
	void RotateTowardsVelocity(float DeltaTime);


	// Camera Lock-on
	bool isCameraLocked;
	FRotator CameraTargetRotator;
	bool HasLockOnTarget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchCamera(float Value);
	void YawCamera(float Value);
	void RotateSpringArm(float DeltaTime);

	void JumpAction();
	void SprintAction();
	void StopSprintAction();
	void LockCameraAction();
	void UnlockCameraAction();
	UFUNCTION(BlueprintImplementableEvent)
		void LightAttackAction();
	
};
