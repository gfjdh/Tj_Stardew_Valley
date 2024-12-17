// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmSpot.h"

// Sets default values
AFarmSpot::AFarmSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	FVector FarmSpotSize(30.0f, 24.0f, 20.0f);
	BoxComp->SetBoxExtent(FarmSpotSize);
}

// Called when the game starts or when spawned
void AFarmSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

