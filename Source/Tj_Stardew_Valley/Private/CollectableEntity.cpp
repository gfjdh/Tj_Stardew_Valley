// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableEntity.h"

// Sets default values
ACollectableEntity::ACollectableEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectableEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

