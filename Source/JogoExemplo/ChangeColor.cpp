// Fill out your copyright notice in the Description page of Project Settings.

#include "JogoExemplo.h"
#include "ChangeColor.h"
#include "Personagem.h"


// Sets default values
AChangeColor::AChangeColor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>
		(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this,
		&AChangeColor::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this,
		&AChangeColor::OnOverlapEnd);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> Material(
		TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	if (Material.Succeeded()) {
		MeshComp->SetMaterial(0, Material.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AChangeColor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChangeColor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AChangeColor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {

	if (OtherActor != nullptr && 
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);

		if (Personagem->GetCollected() == 5) {

			UMaterial* Material = Cast<UMaterial>
				(StaticLoadObject(UMaterial::StaticClass(), NULL,
					TEXT("Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'")));
			if (Material != nullptr) {
				MeshComp->SetMaterial(0, Material);
			}

		}

	}

}

void AChangeColor::OnOverlapEnd(UPrimitiveComponent*
	OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32
	OtherBodyIndex) {

	if (OtherActor != nullptr && 
		OtherActor->IsA(APersonagem::StaticClass())) {

		APersonagem* Personagem = Cast<APersonagem>(OtherActor);

		if (Personagem->GetCollected() == 5) {

			UMaterial* Material = Cast<UMaterial>
				(StaticLoadObject(UMaterial::StaticClass(), NULL,
					TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'")));
			if (Material != nullptr) {
				MeshComp->SetMaterial(0, Material);
			}

		}

	}

}