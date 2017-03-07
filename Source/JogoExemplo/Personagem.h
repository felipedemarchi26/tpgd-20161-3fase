// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Personagem.generated.h"

UCLASS()
class JOGOEXEMPLO_API APersonagem : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Jump() override;

	int GetCollected();

	void SetCollected(int NewCollected);

private:

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Pontuacao")
	int Collected;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* JumpAnim;

	void Move(float Value);

	void MoveSides(float Value);

	void OnCrouch();

	void OnUncrouch();


	
};
