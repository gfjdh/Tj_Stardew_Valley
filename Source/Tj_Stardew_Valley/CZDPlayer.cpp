#include "CZDPlayer.h"
#include "GameFramework/Character.h"
#include "PaperCharacter.generated.h"
// Sets default values
ACZDPlayer::ACZDPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the flipbook component and attach it to the root component
	PlayerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerFlipbook'/Game/Assets/Player/Player_Animation/walk_down/walk_down_at.uasset"));
	PlayerFlipbook->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACZDPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACZDPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACZDPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}