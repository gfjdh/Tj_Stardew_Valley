// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPoint.h"

// Sets default values
ATeleportPoint::ATeleportPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TeleportArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportArea"));
	SetRootComponent(TeleportArea);
}

// Called when the game starts or when spawned
void ATeleportPoint::BeginPlay()
{
	Super::BeginPlay();
	TeleportArea->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPoint::TeleportAreaOverlapBegin);
	//
}

// Called every frame
void ATeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
}

void ATeleportPoint::TeleportAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		Player->SetActorLocation(Target);
	}
}

