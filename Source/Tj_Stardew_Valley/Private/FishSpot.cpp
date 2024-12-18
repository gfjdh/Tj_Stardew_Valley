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

	//ʼλ��
	FVector FishSpawnLocation = GetActorLocation();
	//����λ��x,y����Զ��Player�ķ���ƫ��10-20
	FVector PlayerLocation = Player->GetActorLocation();
	FVector Direction = (FishSpawnLocation - PlayerLocation).GetSafeNormal();
	FishSpawnLocation += Direction * FMath::RandRange(10.0f, 20.0f);
	// ������
	ACollectableEntity* Fish = GetWorld()->SpawnActor<ACollectableEntity>(FishClass, FishSpawnLocation, FRotator::ZeroRotator);
	if (Fish)
	{
		// ������Ч
		UGameplayStatics::PlaySound2D(GetWorld(), FishCaughtSound);
		// ����ͼ��BP_Fish��ʵ��������ƶ�
	}
}
