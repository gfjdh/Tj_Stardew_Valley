// Fill out your copyright notice in the Description page of Project Settings.


#include "MonkeyGold.h"
#include "MyPaperZDCharacter.h"

// Sets default values
AMonkeyGold::AMonkeyGold()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

}

// Called when the game starts or when spawned
void AMonkeyGold::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonkeyGold::OverlapBegin);
}

// Called every frame
void AMonkeyGold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonkeyGold::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		Player->UpdateStamina(-50);
		Player->SDGameInstance->SetPlayerGold(100);
		Player->PlayerUIWidget->SetGold(Player->SDGameInstance->GoldWealth);
	}

}