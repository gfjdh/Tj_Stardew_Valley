#include "NPC.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;

    NPCCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("NPCCapsuleComponent"));
    SetRootComponent(NPCCapsuleComponent);

    NPCFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NPCFlipbookComponent"));
    NPCFlipbookComponent->SetupAttachment(NPCCapsuleComponent);

    MovementAreaCenter = FVector(0.0f, 0.0f, 0.0f);
    MovementAreaRadius = 500.0f;
    MovementSpeed = 100.0f;
    CurrentDirection = FVector::ZeroVector;
    TimeToChangeDirection = 0.0f;

    // 初始化动画指针
    IdleRightAnimation = nullptr;
    IdleLeftAnimation = nullptr;
    IdleUpAnimation = nullptr;
    IdleDownAnimation = nullptr;
    MoveRightAnimation = nullptr;
    MoveLeftAnimation = nullptr;
    MoveUpAnimation = nullptr;
    MoveDownAnimation = nullptr;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveRandomly(DeltaTime);
    ANPC::UpdateAnimation();
}

void ANPC::MoveRandomly(float DeltaTime)
{
    // 更新NPC的方向
    if (TimeToChangeDirection <= 0.0f)
    {
        // 设置一个随机方向
        CurrentDirection = FMath::VRand();
        CurrentDirection.Z = 0.0f; // 在2D平面上移动
        CurrentDirection.Normalize();

        // 设置一个随机时间来改变方向
        TimeToChangeDirection = FMath::RandRange(1.0f, 3.0f);
    }

    // 移动NPC
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // 确保NPC不会移出指定的区域
    if (FVector::Dist(NewLocation, MovementAreaCenter) > MovementAreaRadius)
    {
        NewLocation = MovementAreaCenter + (NewLocation - MovementAreaCenter).GetSafeNormal() * MovementAreaRadius;
        CurrentDirection = -CurrentDirection; // 反转方向
    }

    SetActorLocation(NewLocation);

    // 减少时间
    TimeToChangeDirection -= DeltaTime;
}

void ANPC::UpdateAnimation()
{
    if (CurrentDirection.IsNearlyZero())
    {
        // Idle animations
        if (FMath::Abs(CurrentDirection.X) > FMath::Abs(CurrentDirection.Y))
        {
            if (CurrentDirection.X > 0)
            {
                NPCFlipbookComponent->SetFlipbook(IdleRightAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(IdleLeftAnimation);
            }
        }
        else
        {
            if (CurrentDirection.Y > 0)
            {
                NPCFlipbookComponent->SetFlipbook(IdleUpAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(IdleDownAnimation);
            }
        }
    }
    else
    {
        // Move animations
        if (FMath::Abs(CurrentDirection.X) > FMath::Abs(CurrentDirection.Y))
        {
            if (CurrentDirection.X > 0)
            {
                NPCFlipbookComponent->SetFlipbook(MoveRightAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(MoveLeftAnimation);
            }
        }
        else
        {
            if (CurrentDirection.Y > 0)
            {
                NPCFlipbookComponent->SetFlipbook(MoveUpAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(MoveDownAnimation);
            }
        }
    }
}
