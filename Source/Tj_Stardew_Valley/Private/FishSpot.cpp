#include "FishSpot.h"

AFishSpot::AFishSpot()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
}

void AFishSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFishSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFishSpot::Fishgame()
{
	//Fish Game
}

