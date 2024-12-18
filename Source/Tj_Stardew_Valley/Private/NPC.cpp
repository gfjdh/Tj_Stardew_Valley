#include "NPC.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;
    IsAlive = true;
    CanMove = true;
    MoveStarted = false;

    NPC_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    SetRootComponent(NPC_CapsuleComponent);

    NPCFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NPCFlipbook"));
    NPCFlipbook->SetupAttachment(RootComponent);
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}