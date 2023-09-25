// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MoveCharacter.generated.h"

UCLASS()
class RUSHGAME_API AMoveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMoveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic")
		bool bRunning;

protected:
	void MoveRight(float ScaleValue);

	void Jump_Start();
	void Jump_Stop();
};
