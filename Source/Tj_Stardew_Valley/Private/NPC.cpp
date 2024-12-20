#include "NPC.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

const int DialogueOfTrade = 5;

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;
    // 创建一个胶囊组件作为根组件
    NPCCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("NPCCapsuleComponent"));
    SetRootComponent(NPCCapsuleComponent);

    // 设置碰撞属性
    NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);// 设置碰撞属性为查询和物理
    NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);// 设置碰撞对象类型为Pawn
    NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);// 设置碰撞响应为阻塞
    // 创建一个Flipbook组件作为NPC的视觉组件
    NPCFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NPCFlipbookComponent"));
    NPCFlipbookComponent->SetupAttachment(NPCCapsuleComponent);
    // 创建一个文本组件用于显示对话
    DialogueWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogueWidgetComponent"));
    DialogueWidgetComponent->SetupAttachment(NPCCapsuleComponent);// 设置对话组件的父组件为胶囊组件
    DialogueWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);// 设置对话组件的空间为屏幕空间
    DialogueWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));// 设置对话组件的大小
    DialogueWidgetComponent->SetVisibility(false);// 设置对话组件不可见
    DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));// 设置对话组件的位置
    // 初始化性别属性
    Gender = ENPCGender::Male;
    // 设置自定义Widget类
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/BluePrints/NPC/DialogueWidget"));// 设置对话组件的Widget类
    if (WidgetClass.Succeeded())// 如果找到了Widget类
    {
        DialogueWidgetComponent->SetWidgetClass(WidgetClass.Class);// 设置对话组件的Widget类
    }

    // 设置NPC的移动区域
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

    // 初始化好感度
    Favorability = 0;
	FavorabilityLevel = 0;

    // 初始化对话可见性状态
    bIsDialogueVisible = false;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();

    // 初始化对话内容
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

    // 检测玩家是否靠近并触发对话
    CheckForPlayerInteractionBox();
}

// 随机选择一个对话字符串并显示
void ANPC::DisplayRandomDialogue(int LinesId)
{
    if (DialogueLines.Num() > 0 && DialogueLines.Contains(LinesId))
    {
        const TArray<FString> &CurrentDialogueLines = DialogueLines[LinesId].Lines;
        if (CurrentDialogueLines.Num() > 0)
        {
            int32 RandomIndex = RandomStream.RandRange(0, CurrentDialogueLines.Num() - 1);
            FString RandomDialogue = CurrentDialogueLines[RandomIndex];

            // 获取对话框组件的UserWidget对象
            UUserWidget *DialogueWidget = DialogueWidgetComponent->GetUserWidgetObject();
            if (DialogueWidget)
            {
                UTextBlock *DialogueText = Cast<UTextBlock>(DialogueWidget->GetWidgetFromName(TEXT("DialogueText")));
                if (DialogueText)
                {
                    DialogueText->SetText(FText::FromString(RandomDialogue));// 设置对话文本
                }
            }

            DialogueWidgetComponent->SetVisibility(true);
            bIsDialogueVisible = true;

            // 确保对话框组件的位置在NPC的头顶
            FVector NPCPosition = GetActorLocation();
            DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 5.0f, 15.0f));
        }
    }
}

void ANPC::ReceiveGift(UItem *GiftItem)
{
    if (GiftItem)
    {
        // 根据礼物类型和ID增加好感度
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
// 增加好感度
void ANPC::IncreaseFavorability(int value)
{
    Favorability = Favorability + value;
    CheckFavorabilityLevel();
}
//判断好感度等级
void ANPC::CheckFavorabilityLevel()
{
	//输出调试信息Favorability
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Favorability: %d"), Favorability));
    if (Favorability < 5)
    {
        FavorabilityLevel = 0; // 低好感度
    }
    else if (Favorability < 10)
    {
        FavorabilityLevel = 1; // 中等好感度
    }
    else if (Favorability < 20)
    {
        FavorabilityLevel = 2; // 高好感度
    }
    else
    {
        FavorabilityLevel = 3; // 极高好感度
    }
}
// 获取NPC的碰撞盒
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
// 检测玩家是否靠近
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
			// 检查玩家是否使用了物品
            UItem *UsingItem = Player->PlayerInventory->UseItem();
            // 获取玩家的互动碰撞箱
            UBoxComponent *InteractionBox = GetPlayerInteractionBox(Player);
            if (InteractionBox && InteractionBox->IsOverlappingActor(this)) {
                if (UsingItem == nullptr || UsingItem->ItemType != CollectableType::Gift) {
                    IncreaseFavorability();
                    DisplayRandomDialogue(FavorabilityLevel);
                    CurrentDirection = FVector::ZeroVector;
                    bPlayerNearby = true;
                    DialogueCooldown = 3.0f; // 设置冷却时间为3秒
                    break;
                }
                else if (UsingItem->ItemType == CollectableType::Gift) {
                    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Using type:Gift!")));
                    CurrentDirection = FVector::ZeroVector;
                    bPlayerNearby = true;
                    DialogueCooldown = 3.0f; // 设置冷却时间为3秒
                    // NPC接收礼物
                    this->ReceiveGift(UsingItem);
                    // 从玩家的背包中移除礼物
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

//用于让NPC在指定的区域内随机移动。
void ANPC::MoveRandomly(float DeltaTime)
{
    // 更新NPC的方向
    if (TimeToChangeDirection <= 0.0f)
    {
        // 设置一个随机方向（上、下、左、右）
        int32 Direction = RandomStream.RandRange(0, 4);
        switch (Direction)
        {
            case 4:
                CurrentDirection = FVector(0.0f, 0.0f, 0.0f); // 停止
                break;
            case 3:
                CurrentDirection = FVector(1.0f, 0.0f, 0.0f); // 右
                break;
            case 2:
                CurrentDirection = FVector(-1.0f, 0.0f, 0.0f); // 左
                break;
            case 1:
                CurrentDirection = FVector(0.0f, -1.0f, 0.0f); // 上
                break;
            case 0:
                CurrentDirection = FVector(0.0f, 1.0f, 0.0f); // 下
                break;
        }
        // 设置一个随机时间来改变方向
        TimeToChangeDirection = RandomStream.RandRange(1.0f, 3.0f);
    }

    // 移动NPC
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // 碰撞检测
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
        // 碰到障碍物，反转方向
        CurrentDirection = -CurrentDirection;
        NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);
    }
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

//用于根据NPC的方向来更新NPC的动画。
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
