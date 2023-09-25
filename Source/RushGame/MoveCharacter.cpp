// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMoveCharacter::AMoveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoReceiveInput = EAutoReceiveInput::Player0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 170.0f));
	Camera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMoveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRunning)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction);
	}
}

// Called to bind functionality to input
void AMoveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMoveCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMoveCharacter::Jump_Start);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMoveCharacter::Jump_Stop);
}

void AMoveCharacter::MoveRight(float ScaleValue)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, ScaleValue);
}

void AMoveCharacter::Jump_Start()
{
	bPressedJump = true;
}

void AMoveCharacter::Jump_Stop()
{
	bPressedJump = false;
}