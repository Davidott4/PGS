// Fill out your copyright notice in the Description page of Project Settings.

#include "PGSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APGSCharacter::APGSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MinCameraPitch = -70.0f;
	MaxCameraPitch = 70.0f;
	CameraSpeed = 1.0f;

	// GetMovementComponent()->StopMovementImmediately();
	HasLockOnTarget = false;
	isCameraLocked = false;
	LeanDelta = FRotator(0.0f);
}

// Called when the game starts or when spawned
void APGSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APGSCharacter::SetAnimationVariables()
{
	RunVelocity = GetVelocity().Size();
	
}

void APGSCharacter::MoveForward(float Value)
{
	ForwardInput = Value;
}

void APGSCharacter::MoveRight(float Value)
{

	RightInput = Value;
}



void APGSCharacter::PitchCamera(float Value)
{
	CameraPitch = Value * CameraSpeed;
	/*
	Value *= CameraSpeed;
	FRotator FinalRotation = SpringArmComp->GetComponentRotation();
	FinalRotation = FRotator(FMath::Clamp(FinalRotation.Pitch + Value, MinCameraPitch, MaxCameraPitch), FinalRotation.Yaw, FinalRotation.Roll);
	SpringArmComp->SetWorldRotation(FinalRotation);
	*/
}

void APGSCharacter::YawCamera(float Value)
{
	CameraYaw = Value * CameraSpeed;
	/*
	Value *= CameraSpeed;
	FRotator FinalRotation = SpringArmComp->GetComponentRotation();
	FinalRotation = FRotator(FinalRotation.Pitch, FinalRotation.Yaw + Value, FinalRotation.Roll);
	SpringArmComp->SetWorldRotation(FinalRotation);
	*/
}

void APGSCharacter::RotateSpringArm(float DeltaTime)
{
	FRotator CurrentRotation = SpringArmComp->GetComponentRotation();
	FRotator TargetRotation = FRotator(FMath::Clamp(CurrentRotation.Pitch + CameraPitch, MinCameraPitch, MaxCameraPitch), CurrentRotation.Yaw + CameraYaw, CurrentRotation.Roll);
	//FRotator FinalRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, CameraSpeed*100);
	
	SpringArmComp->SetWorldRotation(TargetRotation);
}

void APGSCharacter::JumpAction()
{
	// TODO
	Jump();
}

void APGSCharacter::SprintAction()
{

}

void APGSCharacter::StopSprintAction()
{

}


void APGSCharacter::LockCameraAction()
{

	if (!HasLockOnTarget)
	{
		CameraTargetRotator = FRotator(GetActorForwardVector().Rotation());
	}
	// TODO: Add Target Logic
}

void APGSCharacter::UnlockCameraAction()
{
	HasLockOnTarget = false;
	isCameraLocked = false;
}

void APGSCharacter::MoveCharacter()
{
	FRotator ControlRot = GetControlRotation();
	
	
	FVector ForwardVec = FVector::VectorPlaneProject(SpringArmComp->GetForwardVector(), FVector::UpVector);
	ForwardVec = ForwardVec.GetSafeNormal();
	FVector RightVec = FVector::VectorPlaneProject(SpringArmComp->GetRightVector(), FVector::UpVector);
	RightVec = RightVec.GetSafeNormal();
	AddMovementInput(ForwardVec * ForwardInput);
	AddMovementInput(RightVec * RightInput);
	SetAnimationVariables();
	
}

void APGSCharacter::RotateTowardsVelocity(float DeltaTime)
{
	FVector Velocity = GetVelocity();
	if (Velocity.Size() > 0.5f)
	{
		FVector CurrentDirection = GetActorForwardVector();
		FVector TargetDirection = Velocity;
		FRotator NewDirection = FMath::RInterpTo(CurrentDirection.ToOrientationRotator(), TargetDirection.ToOrientationRotator(), DeltaTime, Velocity.Size());
		NewDirection = FRotator(NewDirection.Pitch, NewDirection.Yaw - 90.0f, NewDirection.Roll);
		// Set Lean Delta for Animation
		LeanDelta = FRotator(GetVelocity().Rotation() - GetControlRotation());
		GetMesh()->SetWorldRotation(NewDirection);
	}
	
}

// Called every frame
void APGSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCharacter();
	RotateSpringArm(DeltaTime);

	if (FMath::Abs(ForwardInput) > .1 || FMath::Abs(RightInput) > .1)
	{
		RotateTowardsVelocity(DeltaTime);
	}
}



