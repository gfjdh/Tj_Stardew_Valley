#include "Ores.h"
#include "MyPaperZDCharacter.h"

AOres::AOres()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	OreSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	OreSprite->SetupAttachment(RootComponent);

}

void AOres::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AOres::OverlapBegin);

}

void AOres::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOres::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Can be mined"));
	}

}

void AOres::Mine(AActor* OtherActor, USkillStates* PlayerSkill)
{
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//判断是否挖完
		int damage = 1;
		if (Player->PlayerInventory->CurrentItem()->ItemID == 55) {
			damage++;
		}
		Health -= damage;
		if (Health > 0) {
			return;
		}
		int DropNumber = FMath::RandRange(MinDropNumber, MaxDropNumber);
		while (DropNumber--) {
			//远离玩家随机5-30的位置
			FVector Location = GetActorLocation();
			FVector PlayerLocation = OtherActor->GetActorLocation();
			FVector Direction = Location - PlayerLocation;
			Direction.Normalize();
			Location += Direction * FMath::RandRange(5, 30);
			for (int i = 0; i < PlayerSkill->ToolHarvest.SkillStage; i++) {
				ACollectableEntity* Product = GetWorld()->SpawnActor<ACollectableEntity>(ProductClass, Location, FRotator::ZeroRotator);
			}
		}
		//销毁自己
		Destroy();
	}
}
