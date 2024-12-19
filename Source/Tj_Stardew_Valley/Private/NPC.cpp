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

    MovementAreaCenter = FVector(-150.0f, -150.0f, 0.0f); // ����NPC���ƶ���������
    MovementAreaRadius = 100.0f; // ����NPC���ƶ�����뾶
    MovementSpeed = 10.0f; // ����NPC���ƶ��ٶ�
    CurrentDirection = FVector::ZeroVector; // ��ʼ��NPC�ķ���
    TimeToChangeDirection = 0.0f; // ��ʼ��ʱ��

    // ��ʼ������ָ��
    IdleRightAnimation = nullptr;
    IdleLeftAnimation = nullptr;
    IdleUpAnimation = nullptr;
    IdleDownAnimation = nullptr;
    MoveRightAnimation = nullptr;
    MoveLeftAnimation = nullptr;
    MoveUpAnimation = nullptr;
    MoveDownAnimation = nullptr;

    // ��ʼ�������������
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
    // ����NPC�ķ���
    if (TimeToChangeDirection <= 0.0f)
    {
        // ����һ����������ϡ��¡����ң�
        int32 Direction = RandomStream.RandRange(0, 3);
        switch (Direction)
        {
            case 3:
                CurrentDirection = FVector(1.0f, 0.0f, 0.0f); // ��
                break;
            case 2:
                CurrentDirection = FVector(-1.0f, 0.0f, 0.0f); // ��
                break;
            case 1:
                CurrentDirection = FVector(0.0f, 1.0f, 0.0f); // ��
                break;
            case 0:
                CurrentDirection = FVector(0.0f, -1.0f, 0.0f); // ��
                break;
        }
        // ����һ�����ʱ�����ı䷽��
        TimeToChangeDirection = RandomStream.RandRange(1.0f, 3.0f);
    }

    // �ƶ�NPC
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // ȷ��NPC�����Ƴ�ָ��������
    if (FVector::Dist(NewLocation, MovementAreaCenter) > MovementAreaRadius)
    {
        NewLocation = MovementAreaCenter + (NewLocation - MovementAreaCenter).GetSafeNormal() * MovementAreaRadius;
        CurrentDirection = -CurrentDirection; // ��ת����
    }

    SetActorLocation(NewLocation);

    // ����ʱ��
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
