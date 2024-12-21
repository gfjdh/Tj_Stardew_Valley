#include "CookPot.h"
#include "MyPaperZDCharacter.h"

ACookPot::ACookPot()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	PotSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PotSprite"));
	PotSprite->SetupAttachment(RootComponent);
}

void ACookPot::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACookPot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACookPot::OpenCookMenu(AActor* OtherActor)
{
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//´ò¿ªÅëâ¿²Ëµ¥
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Open Cook Menu"));
		Player->CookWidget->SetVisibility(true);
	}
}

