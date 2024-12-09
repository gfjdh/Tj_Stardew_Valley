// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeStump.h"
#include "MyPaperZDCharacter.h"

// Sets default values
ATreeStump::ATreeStump()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	TreeSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	TreeSprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATreeStump::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ATreeStump::OverlapBegin);
	
}

// Called every frame
void ATreeStump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreeStump::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Can be chopped"));
	}

}

void ATreeStump::Chop(AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Chopped"));
	//写出逻辑:掉落物品等等
	int ExpValue = 0;//需要修改
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		Player->UpdateLevel(ExpValue);
	}
}