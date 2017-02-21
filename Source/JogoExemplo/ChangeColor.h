// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChangeColor.generated.h"

UCLASS()
class JOGOEXEMPLO_API AChangeColor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChangeColor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	
};
