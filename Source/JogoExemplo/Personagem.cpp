// Fill out your copyright notice in the Description page of Project Settings.

#include "JogoExemplo.h"
#include "Personagem.h"
#include "ProjectileActor.h"


// Sets default values
APersonagem::APersonagem()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		AnimWalk(TEXT("AnimBlueprint'/Game/Animations/WalkAnimation.WalkAnimation'"));
	if (AnimWalk.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimWalk.Object->
			GetAnimBlueprintGeneratedClass());
	}

	ConstructorHelpers::FObjectFinder<UAnimSequence>
		JumpLoad(TEXT("AnimSequence'/Game/AnimStarterPack/Jump_From_Stand.Jump_From_Stand'"));
	if (JumpLoad.Succeeded()) {
		JumpAnim = JumpLoad.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		WalkLoad(TEXT("AnimBlueprint'/Game/Animations/WalkAnimation.WalkAnimation'"));
	if (WalkLoad.Succeeded()) {
		WalkAnim = WalkLoad.Object->GetAnimBlueprintGeneratedClass();
	}

	ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		CrouchLoad(TEXT("AnimBlueprint'/Game/Animations/CrouchAnimation.CrouchAnimation'"));
	if (CrouchLoad.Succeeded()) {
		CrouchAnim = CrouchLoad.Object->GetAnimBlueprintGeneratedClass();
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	if (GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode
		&& GetCharacterMovement()->IsMovingOnGround()) {

		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	}

}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Move", this, &APersonagem::Move);
	InputComponent->BindAxis("Side", this, &APersonagem::MoveSides);

	InputComponent->BindAction("Jump", IE_Pressed, this,
		&APersonagem::Jump);
	InputComponent->BindAction("Jump", IE_Released, this,
		&ACharacter::StopJumping);
	InputComponent->BindAction("Crouch", IE_Pressed, this,
		&APersonagem::OnCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this,
		&APersonagem::OnUncrouch);
	InputComponent->BindAction("Run", IE_Pressed, this,
		&APersonagem::StartRun);
	InputComponent->BindAction("Run", IE_Released, this,
		&APersonagem::StopRun);
	InputComponent->BindAction("Drop", IE_Pressed, this,
		&APersonagem::DropProjectile);
}

//Método que movimenta o personagem para frente e para tras.
void APersonagem::Move(float Value) {
	FVector Forward(1.0f, 0.0f, 0.0f);//X - Y - Z
	AddMovementInput(Forward, Value);
}

//Método que movimenta o personagem para direita e esquerda.
void APersonagem::MoveSides(float Value) {
	FVector Side(0.0f, 1.0f, 0.0f);//X - Y - Z
	AddMovementInput(Side, Value);
}

void APersonagem::OnCrouch() {
	Super::Crouch();
	GetMesh()->SetAnimInstanceClass(CrouchAnim);
}

void APersonagem::OnUncrouch() {
	Super::UnCrouch();
	GetMesh()->SetAnimInstanceClass(WalkAnim);
}

int APersonagem::GetCollected() {
	return Collected;
}

void APersonagem::SetCollected(int NewCollected) {
	Collected = NewCollected;
}

void APersonagem::Jump() {
	Super::Jump();

	if (JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
	}
}

void APersonagem::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void APersonagem::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void APersonagem::DropProjectile() {
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		AProjectileActor* Projectile = 
			World->SpawnActor<AProjectileActor>(GetActorLocation(),
			FRotator::ZeroRotator, SpawnParameters);
	}
}