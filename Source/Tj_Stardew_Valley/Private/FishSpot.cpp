#include "FishSpot.h"
#include "Kismet/GameplayStatics.h"

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

	//始位置
	FVector FishSpawnLocation = GetActorLocation();
	//生成位置x,y朝着远离Player的方向偏离10-20
	FVector PlayerLocation = Player->GetActorLocation();
	FVector Direction = (FishSpawnLocation - PlayerLocation).GetSafeNormal();
	FishSpawnLocation += Direction * FMath::RandRange(10.0f, 20.0f);
	// 生成鱼
	ACollectableEntity* Fish = GetWorld()->SpawnActor<ACollectableEntity>(FishClass, FishSpawnLocation, FRotator::ZeroRotator);
	if (Fish)
	{
		// 播放音效
		UGameplayStatics::PlaySound2D(GetWorld(), FishCaughtSound);
		// 由蓝图在BP_Fish内实现向玩家移动
	}
}
