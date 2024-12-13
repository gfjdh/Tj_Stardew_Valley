// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmLand.h"


// Sets default values
AFarmLand::AFarmLand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	FarmLandSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FarmLandSprite"));
	FarmLandSprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFarmLand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmLand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

