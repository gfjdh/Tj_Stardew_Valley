#include "NPC.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CGameMode.h"
const int DialogueOfTrade = 5;
const int DialogueOfCopleteQuest = 6;
const int DialogueOfAcceptQuest = 7;
const int DialogueOfGiveApple = 8;
const int LowFavorabilityThreshold = 5;
const int MediumFavorabilityThreshold = 10;
const int HighFavorabilityThreshold = 20;

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
    Favorability = 18;
	FavorabilityLevel = 0;

    // ��ʼ���Ի��ɼ���״̬
    bIsDialogueVisible = false;
	bQuestCompleted = true;

    // ��ʼ������
    FQuest Quest1;
	Quest1.QuestName = TEXT("collect 1 pieces of wood");
	Quest1.Description = TEXT("please help me collect 1 pieces of wood.");
    Quest1.RequiredItemIDs = { 100 }; // ľ�ĵ�ID��100
    Quest1.RewardGold = 100;
    Quest1.bIsCompleted = false;
    AvailableQuests.Add(Quest1);

    FQuest Quest2;
	Quest2.QuestName = TEXT("collect 1 Apple");
	Quest2.Description = TEXT("please help me collect 1 Apple.");
	Quest2.RequiredItemIDs = { 60 }; // ƻ����ID��60
    Quest2.RewardGold = 50;
    Quest2.bIsCompleted = false;
    AvailableQuests.Add(Quest2);

	FQuest Quest3;
    Quest3.QuestName = TEXT("collect 1 Apple");
    Quest3.Description = TEXT("please help me collect 1 Apple.");
    Quest3.RequiredItemIDs = { 60 }; // ƻ����ID��60
	Quest3.RewardGold = 50;
	Quest3.bIsCompleted = false;
	AvailableQuests.Add(Quest3);

	bHasGivenAppleToday = false;// ��ʼ������û�и���ƻ��
	LastGiftDay = -1;// ��ʼ���ϴ������������
    GameMode = nullptr;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
    // ��ȡGameMode������
    GameMode = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());
    // ��ʼ���Ի�����
    if (Gender == ENPCGender::Male) {
        DialogueLines.Add(0, { { TEXT("Hey, buddy!"), TEXT("How have you been?"), TEXT("The weather is great today, perfect for a walk!") } });
        DialogueLines.Add(1, { { TEXT("Hi!"), TEXT("I'm good, how about you?"), TEXT("Today is a great day for playing ball!") } });
        DialogueLines.Add(2, { { TEXT("Yo!"), TEXT("Good to see you!"), TEXT("What a beautiful day, isn't it?") } });
        DialogueLines.Add(3, { { TEXT("Hey, bro!"), TEXT("What have you been up to?"), TEXT("Today is a great day for an adventure!") } });
        DialogueLines.Add(DialogueOfTrade, { { TEXT("Thank you very much"), TEXT("Thanks!"), TEXT("You're a good person!") } });
        DialogueLines.Add(DialogueOfCopleteQuest, { { TEXT("Thank you very much"), TEXT("Thanks!"), TEXT("You're a good person!") } });
		DialogueLines.Add(DialogueOfAcceptQuest, { { TEXT("Please help me!") } });
		DialogueLines.Add(DialogueOfGiveApple, { { TEXT("This is for you!" } }));
    }
    else {
        DialogueLines.Add(0, { { TEXT("Hi!"), TEXT("How have you been?"), TEXT("The weather is great today, perfect for shopping!") } });
        DialogueLines.Add(1, { { TEXT("Hello!"), TEXT("I'm good, thank you!"), TEXT("Today is a great day for shopping!") } });
        DialogueLines.Add(2, { { TEXT("Hey!"), TEXT("Good to see you!"), TEXT("What a beautiful day, isn't it?") } });
        DialogueLines.Add(3, { { TEXT("Hi, dear!"), TEXT("What have you been up to?"), TEXT("Today is a great day for a date!") } });
        DialogueLines.Add(DialogueOfTrade, { { TEXT("Wow! This is my favorite gift!"), TEXT("Thank you!"), TEXT("You're a good person!") } });
        DialogueLines.Add(DialogueOfCopleteQuest, { { TEXT("Thank you very much"), TEXT("Thanks!"), TEXT("You're a good person!") } });
        DialogueLines.Add(DialogueOfAcceptQuest, { { TEXT("Please help me!") } });
        DialogueLines.Add(DialogueOfGiveApple, { { TEXT("This is for you!" } }));
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
	if (Favorability == LowFavorabilityThreshold || Favorability == MediumFavorabilityThreshold || Favorability == HighFavorabilityThreshold)
	{
		FavorabilityLevel = -1; // �øжȷֽ�㣬�ȴ�����
    }
    else if (Favorability <= LowFavorabilityThreshold)
    {
        FavorabilityLevel = 0; // �ͺøж�
    }
    else if (Favorability <= MediumFavorabilityThreshold)
    {
        FavorabilityLevel = 1; // �еȺøж�
    }
    else if (Favorability <= HighFavorabilityThreshold)
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
            // ����Ƿ����µ�һ��
            if (GameMode)
            {
                int32 CurrentDay = GameMode->GetCurrentDay();
                if (CurrentDay != LastGiftDay)
                {
                    bHasGivenAppleToday = false;
                    LastGiftDay = CurrentDay;
                }
            }
            // �������Ƿ�ʹ������Ʒ
            UItem *UsingItem = Player->PlayerInventory->UseItem();
            // ��ȡ��ҵĻ�����ײ��
            UBoxComponent *InteractionBox = GetPlayerInteractionBox(Player);
            if (InteractionBox && InteractionBox->IsOverlappingActor(this)) {
                if (UsingItem == nullptr || UsingItem->ItemType != CollectableType::Gift) {
                    if (FavorabilityLevel == -1)
                    {
                        if (AvailableQuests.Num() > 0 && bQuestCompleted)
                        {
                            AssignQuest(Player, AvailableQuests[0]);
                            bQuestCompleted = false;
                        }
                        else if (Player->Quests[0].bIsCompleted) {
                            IncreaseFavorability(1);
                            //ɾ����ɵ�����
                            AvailableQuests.RemoveAt(0);
                            bQuestCompleted = true;
                            DisplayRandomDialogue(DialogueOfCopleteQuest);
                        }
                    }
                    // ����øжȴﵽ����ҵ��컹û�����͹�ƻ��
                    else if (FavorabilityLevel == 3 && !bHasGivenAppleToday)
                    {
                        SpawnItemForPlayer(Player, CollectableEntityClass);
                        bHasGivenAppleToday = true;
                        DisplayRandomDialogue(DialogueOfGiveApple);
                    }
                    else {
                        IncreaseFavorability(1);
                        DisplayRandomDialogue(FavorabilityLevel);
                    }
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
// ������Ʒ
void ANPC::SpawnItemForPlayer(AMyPaperZDCharacter *Player, TSubclassOf<ACollectableEntity> NameOfCollectableEntityClass)
{
    // ʹ��this->��ȷ�������Ա����
    this->CollectableEntityClass = NameOfCollectableEntityClass;
    //ʼλ��
    FVector AppleSpawnLocation = GetActorLocation();
    //����λ��x,y����Player�ķ�����ƫ��20
    FVector PlayerLocation = Player->GetActorLocation();
    FVector Direction = (AppleSpawnLocation - PlayerLocation).GetSafeNormal();
    AppleSpawnLocation += Direction * 20.0f;
    // ����ƻ��
    ACollectableEntity *CollectableEntity = GetWorld()->SpawnActor<ACollectableEntity>(NameOfCollectableEntityClass, AppleSpawnLocation, FRotator::ZeroRotator);
}
// ��������Ƿ����
int ANPC::CheckCompleteQuest()
{
    for (int32 i = 0; i < AvailableQuests.Num(); i++)
    {
        if (!AvailableQuests[i].bIsCompleted)
        {
            return i;
        }
    }
    return -1;
}
// ��������
void ANPC::AssignQuest(AMyPaperZDCharacter *Player, const FQuest &Quest)
{
    if (Player)
    {
        DisplayRandomDialogue(DialogueOfAcceptQuest);
        Player->ReceiveQuest(Quest);
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

