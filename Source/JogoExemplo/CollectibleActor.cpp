// Fill out your copyright notice in the Description page of Project Settings.

#include "JogoExemplo.h"
#include "CollectibleActor.h"
#include "Personagem.h"


// Sets default values
ACollectibleActor::ACollectibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>
		(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleActor::OnOverlapBegin);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACollectibleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectibleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACollectibleActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		Personagem->SetCollected(Personagem->GetCollected() + 1);
		UE_LOG(LogTemp, Warning, TEXT("Pontuação: %d"), Personagem->GetCollected());
		Destroy();
	}
}