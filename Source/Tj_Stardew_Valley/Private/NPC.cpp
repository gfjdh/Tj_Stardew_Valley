#include "NPC.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

const int DialogueOfTrade = 5;

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;
    // ����һ�����������Ϊ�����
    NPCCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("NPCCapsuleComponent"));
    SetRootComponent(NPCCapsuleComponent);

    // ������ײ����
    NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);// ������ײ����Ϊ��ѯ������
    NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);// ������ײ��������ΪPawn
    NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);// ������ײ��ӦΪ����
    // ����һ��Flipbook�����ΪNPC���Ӿ����
    NPCFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NPCFlipbookComponent"));
    NPCFlipbookComponent->SetupAttachment(NPCCapsuleComponent);
    // ����һ���ı����������ʾ�Ի�
    DialogueWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogueWidgetComponent"));
    DialogueWidgetComponent->SetupAttachment(NPCCapsuleComponent);// ���öԻ�����ĸ����Ϊ�������
    DialogueWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);// ���öԻ�����Ŀռ�Ϊ��Ļ�ռ�
    DialogueWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));// ���öԻ�����Ĵ�С
    DialogueWidgetComponent->SetVisibility(false);// ���öԻ�������ɼ�
    DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));// ���öԻ������λ��
    // ��ʼ���Ա�����
    Gender = ENPCGender::Male;
    // �����Զ���Widget��
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/BluePrints/NPC/DialogueWidget"));// ���öԻ������Widget��
    if (WidgetClass.Succeeded())// ����ҵ���Widget��
    {
        DialogueWidgetComponent->SetWidgetClass(WidgetClass.Class);// ���öԻ������Widget��
    }

    // ����NPC���ƶ�����
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

    // ��ʼ���øж�
    Favorability = 0;
	FavorabilityLevel = 0;

    // ��ʼ���Ի��ɼ���״̬
    bIsDialogueVisible = false;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();

    // ��ʼ���Ի�����
    if (Gender == ENPCGender::Male) {
        DialogueLines.Add(0, { { TEXT("Hey, buddy!"), TEXT("How have you been?"), TEXT("The weather is great today, perfect for a walk!") } });
        DialogueLines.Add(1, { { TEXT("Hi!"), TEXT("I'm good, how about you?"), TEXT("Today is a great day for playing ball!") } });
        DialogueLines.Add(2, { { TEXT("Yo!"), TEXT("Good to see you!"), TEXT("What a beautiful day, isn't it?") } });
        DialogueLines.Add(3, { { TEXT("Hey, bro!"), TEXT("What have you been up to?"), TEXT("Today is a great day for an adventure!") } });
        DialogueLines.Add(DialogueOfTrade, { { TEXT("Thank you very much"), TEXT("Thanks!"), TEXT("You're a good person!") } });
    }
    else {
        DialogueLines.Add(0, { { TEXT("Hi!"), TEXT("How have you been?"), TEXT("The weather is great today, perfect for shopping!") } });
        DialogueLines.Add(1, { { TEXT("Hello!"), TEXT("I'm good, thank you!"), TEXT("Today is a great day for shopping!") } });
        DialogueLines.Add(2, { { TEXT("Hey!"), TEXT("Good to see you!"), TEXT("What a beautiful day, isn't it?") } });
        DialogueLines.Add(3, { { TEXT("Hi, dear!"), TEXT("What have you been up to?"), TEXT("Today is a great day for a date!") } });
        DialogueLines.Add(DialogueOfTrade, { { TEXT("Wow! This is my favorite gift!"), TEXT("Thank you!"), TEXT("You're a good person!") } });
    }

}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveRandomly(DeltaTime);
    ANPC::UpdateAnimation();

    // �������Ƿ񿿽��������Ի�
    CheckForPlayerInteractionBox();
}

// ���ѡ��һ���Ի��ַ�������ʾ
void ANPC::DisplayRandomDialogue(int LinesId)
{
    if (DialogueLines.Num() > 0 && DialogueLines.Contains(LinesId))
    {
        const TArray<FString> &CurrentDialogueLines = DialogueLines[LinesId].Lines;
        if (CurrentDialogueLines.Num() > 0)
        {
            int32 RandomIndex = RandomStream.RandRange(0, CurrentDialogueLines.Num() - 1);
            FString RandomDialogue = CurrentDialogueLines[RandomIndex];

            // ��ȡ�Ի��������UserWidget����
            UUserWidget *DialogueWidget = DialogueWidgetComponent->GetUserWidgetObject();
            if (DialogueWidget)
            {
                UTextBlock *DialogueText = Cast<UTextBlock>(DialogueWidget->GetWidgetFromName(TEXT("DialogueText")));
                if (DialogueText)
                {
                    DialogueText->SetText(FText::FromString(RandomDialogue));// ���öԻ��ı�
                }
            }

            DialogueWidgetComponent->SetVisibility(true);
            bIsDialogueVisible = true;

            // ȷ���Ի��������λ����NPC��ͷ��
            FVector NPCPosition = GetActorLocation();
            DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 5.0f, 15.0f));
        }
    }
}

void ANPC::ReceiveGift(UItem *GiftItem)
{
    if (GiftItem)
    {
        // �����������ͺ�ID���Ӻøж�
        int32 FavorabilityIncrease = 0;
        switch (GiftItem->ItemID)
        {
            case 70:
                FavorabilityIncrease = 50;
                break;
            default:
                FavorabilityIncrease = 10;
                break;
        }
        IncreaseFavorability(FavorabilityIncrease);
        DisplayRandomDialogue(DialogueOfTrade);
    }
}

bool ANPC::TradeWithPlayer(int32 GoldAmount)
{
    if (GoldAmount > 0)
    {
        
        return true;
    }
    return false;
}
// ���Ӻøж�
void ANPC::IncreaseFavorability(int value)
{
    Favorability = Favorability + value;
    CheckFavorabilityLevel();
}
//�жϺøжȵȼ�
void ANPC::CheckFavorabilityLevel()
{
	//���������ϢFavorability
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Favorability: %d"), Favorability));
    if (Favorability < 5)
    {
        FavorabilityLevel = 0; // �ͺøж�
    }
    else if (Favorability < 10)
    {
        FavorabilityLevel = 1; // �еȺøж�
    }
    else if (Favorability < 20)
    {
        FavorabilityLevel = 2; // �ߺøж�
    }
    else
    {
        FavorabilityLevel = 3; // ���ߺøж�
    }
}
// ��ȡNPC����ײ��
UBoxComponent *ANPC::GetPlayerInteractionBox(AMyPaperZDCharacter *Player)
{
    if (!Player) return nullptr;

    UBoxComponent *InteractionBox = nullptr;
    switch (Player->PlayerDirection)
    {
        case EPlayerDirection::Up:
            InteractionBox = Player->InteractionBoxUp;
            break;
        case EPlayerDirection::Down:
            InteractionBox = Player->InteractionBoxDown;
            break;
        case EPlayerDirection::Left:
            InteractionBox = Player->InteractionBoxLeft;
            break;
        case EPlayerDirection::Right:
            InteractionBox = Player->InteractionBoxRight;
            break;
    }
    return InteractionBox;
}
// �������Ƿ񿿽�
void ANPC::CheckForPlayerInteractionBox()
{
    static float DialogueCooldown = 0.0f;

    if (DialogueCooldown > 0.0f)
    {
        DialogueCooldown -= GetWorld()->GetDeltaSeconds();
        return;
    }

    TArray<AActor *> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AMyPaperZDCharacter::StaticClass());

    bool bPlayerNearby = false;

    for (AActor *Actor : OverlappingActors)
    {
        AMyPaperZDCharacter *Player = Cast<AMyPaperZDCharacter>(Actor);
        if (Player)
        {
			// �������Ƿ�ʹ������Ʒ
            UItem *UsingItem = Player->PlayerInventory->UseItem();
            // ��ȡ��ҵĻ�����ײ��
            UBoxComponent *InteractionBox = GetPlayerInteractionBox(Player);
            if (InteractionBox && InteractionBox->IsOverlappingActor(this)) {
                if (UsingItem == nullptr || UsingItem->ItemType != CollectableType::Gift) {
                    IncreaseFavorability();
                    DisplayRandomDialogue(FavorabilityLevel);
                    CurrentDirection = FVector::ZeroVector;
                    bPlayerNearby = true;
                    DialogueCooldown = 3.0f; // ������ȴʱ��Ϊ3��
                    break;
                }
                else if (UsingItem->ItemType == CollectableType::Gift) {
                    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Using type:Gift!")));
                    CurrentDirection = FVector::ZeroVector;
                    bPlayerNearby = true;
                    DialogueCooldown = 3.0f; // ������ȴʱ��Ϊ3��
                    // NPC��������
                    this->ReceiveGift(UsingItem);
                    // ����ҵı������Ƴ�����
                    Player->PlayerInventory->RemoveItemByIndex(Player->PlayerInventory->UsingIndex, 1);
                    break;
                }
            }
        }
    }

    if (!bPlayerNearby && bIsDialogueVisible)
    {
        DialogueWidgetComponent->SetVisibility(false);
        bIsDialogueVisible = false;
    }
}

//������NPC��ָ��������������ƶ���
void ANPC::MoveRandomly(float DeltaTime)
{
    // ����NPC�ķ���
    if (TimeToChangeDirection <= 0.0f)
    {
        // ����һ����������ϡ��¡����ң�
        int32 Direction = RandomStream.RandRange(0, 4);
        switch (Direction)
        {
            case 4:
                CurrentDirection = FVector(0.0f, 0.0f, 0.0f); // ֹͣ
                break;
            case 3:
                CurrentDirection = FVector(1.0f, 0.0f, 0.0f); // ��
                break;
            case 2:
                CurrentDirection = FVector(-1.0f, 0.0f, 0.0f); // ��
                break;
            case 1:
                CurrentDirection = FVector(0.0f, -1.0f, 0.0f); // ��
                break;
            case 0:
                CurrentDirection = FVector(0.0f, 1.0f, 0.0f); // ��
                break;
        }
        // ����һ�����ʱ�����ı䷽��
        TimeToChangeDirection = RandomStream.RandRange(1.0f, 3.0f);
    }

    // �ƶ�NPC
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // ��ײ���
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        GetActorLocation(),
        NewLocation,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeCapsule(NPCCapsuleComponent->GetScaledCapsuleRadius(), NPCCapsuleComponent->GetScaledCapsuleHalfHeight()),
        CollisionParams
    );

    if (bHit)
    {
        // �����ϰ����ת����
        CurrentDirection = -CurrentDirection;
        NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);
    }
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

//���ڸ���NPC�ķ���������NPC�Ķ�����
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
        else if (CurrentDirection.X == 0 && CurrentDirection.Y < 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveUpAnimation);
        }
        else if (CurrentDirection.X == 0 && CurrentDirection.Y > 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveDownAnimation);
        }
    }
}
