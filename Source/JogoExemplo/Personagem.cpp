// Fill out your copyright notice in the Description page of Project Settings.

#include "JogoExemplo.h"
#include "Personagem.h"


// Sets default values
APersonagem::APersonagem()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void APersonagem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APersonagem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Move", this, &APersonagem::Move);
	InputComponent->BindAxis("Side", this, &APersonagem::MoveSides);

	InputComponent->BindAction("Jump", IE_Pressed, this,
		&ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this,
		&ACharacter::StopJumping);
	InputComponent->BindAction("Crouch", IE_Pressed, this,
		&APersonagem::OnCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this,
		&APersonagem::OnUncrouch);
}

//M�todo que movimenta o personagem para frente e para tras.
void APersonagem::Move(float Value) {
	FVector Forward(1.0f, 0.0f, 0.0f);//X - Y - Z
	AddMovementInput(Forward, Value);
}

//M�todo que movimenta o personagem para direita e esquerda.
void APersonagem::MoveSides(float Value) {
	FVector Side(0.0f, 1.0f, 0.0f);//X - Y - Z
	AddMovementInput(Side, Value);
}

void APersonagem::OnCrouch() {
	Super::Crouch();
}

void APersonagem::OnUncrouch() {
	Super::UnCrouch();
}

int APersonagem::GetCollected() {
	return Collected;
}

void APersonagem::SetCollected(int NewCollected) {
	Collected = NewCollected;
}