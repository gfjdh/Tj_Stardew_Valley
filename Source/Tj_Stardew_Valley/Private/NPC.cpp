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

    MovementAreaCenter = FVector(-150.0f, -150.0f, 0.0f); // 设置NPC的移动区域中心
    MovementAreaRadius = 100.0f; // 设置NPC的移动区域半径
    MovementSpeed = 10.0f; // 设置NPC的移动速度
    CurrentDirection = FVector::ZeroVector; // 初始化NPC的方向
    TimeToChangeDirection = 0.0f; // 初始化时间

    // 初始化动画指针
    IdleRightAnimation = nullptr;
    IdleLeftAnimation = nullptr;
    IdleUpAnimation = nullptr;
    IdleDownAnimation = nullptr;
    MoveRightAnimation = nullptr;
    MoveLeftAnimation = nullptr;
    MoveUpAnimation = nullptr;
    MoveDownAnimation = nullptr;

    // 初始化随机数生成器
    RandomStream.Initialize(FDateTime::Now().GetMillisecond());
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
        // 设置一个随机方向（上、下、左、右）
        int32 Direction = RandomStream.RandRange(0, 3);
        switch (Direction)
        {
            case 3:
                CurrentDirection = FVector(1.0f, 0.0f, 0.0f); // 右
                break;
            case 2:
                CurrentDirection = FVector(-1.0f, 0.0f, 0.0f); // 左
                break;
            case 1:
                CurrentDirection = FVector(0.0f, 1.0f, 0.0f); // 上
                break;
            case 0:
                CurrentDirection = FVector(0.0f, -1.0f, 0.0f); // 下
                break;
        }
        // 设置一个随机时间来改变方向
        TimeToChangeDirection = RandomStream.RandRange(1.0f, 3.0f);
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
        if (CurrentDirection.Y == 0 && CurrentDirection.X > 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveRightAnimation);
        }
        else if (CurrentDirection.Y == 0 && CurrentDirection.X < 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveLeftAnimation);
        }
        else if (CurrentDirection.X == 0 && CurrentDirection.Y > 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveUpAnimation);
        }
        else if (CurrentDirection.X == 0 && CurrentDirection.Y < 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveDownAnimation);
        }
    }
}
