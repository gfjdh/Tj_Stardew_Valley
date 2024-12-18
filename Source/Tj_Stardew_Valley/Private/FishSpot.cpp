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
	//get player
	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
	if (PlayerActor) {
		Player = Cast<AMyPaperZDCharacter>(PlayerActor);
		Player->SpawnFishDelegate.AddDynamic(this, &AFishSpot::SpawnFish);
	}
}

void AFishSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFishSpot::SpawnFish()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SpawnFish!"));
}
