// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableEntity.h"
#include "MyPaperZDCharacter.h"

// Sets default values
ACollectableEntity::ACollectableEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	ItemSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ItemSprite"));
	ItemSprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACollectableEntity::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACollectableEntity::OverlapBegin);
}

// Called every frame
void ACollectableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACollectableEntity::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Picked it!"));
		Player->CollectItem(Type);
		Player->UpdateLevel(ExpValue);
		Destroy();
	}

}
