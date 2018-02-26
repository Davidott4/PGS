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



	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchCamera(float Value);
	void YawCamera(float Value);
	void RotateTowardsVelocity(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
