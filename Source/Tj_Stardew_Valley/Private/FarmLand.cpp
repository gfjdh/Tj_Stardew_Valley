// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmLand.h"
#include "GameFramework/Character.h"


// Sets default values
AFarmLand::AFarmLand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	FarmLandSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FarmLandSprite"));
	FarmLandSpriteComp->SetupAttachment(RootComponent);
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
	if (WaterLevel > 10) {
		this->FarmLandSpriteComp->SetSprite(WetFarmLandSprite);
	}
	else {
		this->FarmLandSpriteComp->SetSprite(FarmLandSprite);
	}
	if (WaterLevel > 0) {
		WaterLevel--;
	}
}

//½½Ë®
void AFarmLand::WaterFarmLand()
{
	WaterLevel += 50;
}

