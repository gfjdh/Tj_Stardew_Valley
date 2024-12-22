#include "Merchant.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MerchantWidget.h"

AMerchant::AMerchant()
{
    // 设置商人不需要移动
    PrimaryActorTick.bCanEverTick = true;
    // 设置商人碰撞体积
    NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    // 设置NPC的移动区域
    MovementAreaCenter = FVector(0.0f, -180.0f, 10.0f); // 设置NPC的移动区域中心
    MovementAreaRadius = 0.0f; // 设置NPC的移动区域半径
    MovementSpeed = 0.0f; // 设置NPC的移动速度
    CurrentDirection = FVector::ZeroVector; // 初始化NPC的方向
    TimeToChangeDirection = 0.0f; // 初始化时间
    // 设置商人待机动画
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleAnimation(TEXT("/Game/Animations/IdleAnimation"));
    if (IdleAnimation.Succeeded())
    {
        NPCFlipbookComponent->SetFlipbook(IdleAnimation.Object);
    }

    // 初始化商人类型
    MerchantType = EMerchantType::Vendor;

    // 初始化交易选项
    TradeOptions.Add(TEXT("Buy woods (10 Gold)"));
    TradeOptions.Add(TEXT("Buy apples (15 Gold)"));
    TradeOptions.Add(TEXT("Buy rings (50 Gold)"));

    // 初始化小游戏界面类
    static ConstructorHelpers::FClassFinder<UUserWidget> GameWidget(TEXT("/Game/BluePrints/NPC/BP_GameWidget"));
    if (GameWidget.Succeeded())
    {
        GameWidgetClass = GameWidget.Class;
    }

    // 初始化交易界面类
    static ConstructorHelpers::FClassFinder<UUserWidget> TradeWidget(TEXT("/Game/BluePrints/NPC/BP_TradeWidget"));
    if (TradeWidget.Succeeded())
    {
        TradeWidgetClass = TradeWidget.Class;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to find TradeWidget class!"));
    }
    // 初始化商品数据
    ItemsForSale.Add(10);
    ItemsForSale.Add(15);
    ItemsForSale.Add(50);

    CurrentPlayer = nullptr;
    bTrading = false;
}

void AMerchant::BeginPlay()
{
    Super::BeginPlay();

    // 初始化对话内容
    DialogueLines.Add(0, { { TEXT("Welcome! What can I do for you?") } });
    DialogueLines.Add(1, { { TEXT("Need something? I have the best deals!") } });
    DialogueLines.Add(2, { { TEXT("Want to play a game? It's fun and rewarding!") } });
}

void AMerchant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AMerchant::CheckForPlayerInteractionBox();
}

void AMerchant::ShowTradeMenu()
{
    bTrading = true;
    if (TradeWidgetClass)
    {
        CurrentWidget = CreateWidget<UMerchantWidget>(GetWorld(), TradeWidgetClass);
        if (CurrentWidget)
        {
            Cast<UMerchantWidget>(CurrentWidget)->SetMerchant(this);
            CurrentWidget->AddToViewport();
            APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (PlayerController)
            {
                PlayerController->SetShowMouseCursor(true);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Trade menu displayed!"));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to get PlayerController!"));
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to create TradeWidget!"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TradeWidgetClass is null!"));
    }
}

void AMerchant::ShowGameMenu()
{
    if (GameWidgetClass)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
        if (CurrentWidget)
        {
            Cast<UMerchantWidget>(CurrentWidget)->SetMerchant(this);
            CurrentWidget->AddToViewport();
            APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (PlayerController)
            {
                PlayerController->SetShowMouseCursor(true);
            }
        }
    }
}
// 获取NPC的碰撞盒
UBoxComponent *AMerchant::GetPlayerInteractionBox(AMyPaperZDCharacter *Player)
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
void AMerchant::CheckForPlayerInteractionBox()
{
    static float DialogueCooldown = 0.0f;
    if (DialogueCooldown > 0.0f || bTrading)
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
            // 获取玩家的互动碰撞箱
            UBoxComponent *InteractionBox = GetPlayerInteractionBox(Player);
            if (InteractionBox && InteractionBox->IsOverlappingActor(this)) {
                CurrentPlayer = Player;
				//输出调试信息
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ShowGameMenu!"));
				ShowTradeMenu();
                bPlayerNearby = true;
                DialogueCooldown = 3.0f; // 设置冷却时间为3秒
            }
        }
    }
    if (!bPlayerNearby && bIsDialogueVisible)
    {
        DialogueWidgetComponent->SetVisibility(false);
        bIsDialogueVisible = false;
    }
}

void AMerchant::HandleTrade(int32 OptionIndex, AMyPaperZDCharacter *Player)
{
    if (OptionIndex >= 0 && OptionIndex < ItemsForSale.Num())
    {
        FItemForSale Option = ItemsForSale[OptionIndex];
		if (CheckPlayerGold(ItemsForSale[OptionIndex].Price))
        {
            UpdatePlayerGold(-1 * ItemsForSale[OptionIndex].Price);
            // 给玩家添加物品
            SpawnItemForPlayer(Player, GetCollectableEntityClass(OptionIndex));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You bought a %Item!"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
        }
    }
    CloseCurrentMenu();
}

TSubclassOf<ACollectableEntity> AMerchant::GetCollectableEntityClass(int32 Index)
{
	if (Index == 0)
	{
		return CollectableEntityClass1;
	}
	else if (Index == 1)
	{
		return CollectableEntityClass2;
	}
	else if (Index == 2)
	{
		return CollectableEntityClass3;
	}
	return nullptr;
}

void AMerchant::HandleGame()
{
    if (CheckPlayerGold(20))
    {
        UpdatePlayerGold(-20);
        // 开始小游戏
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game started!"));
        // 小游戏逻辑
        // ...
        // 假设玩家赢了
        int32 Reward = FMath::RandRange(10, 50);
        UpdatePlayerGold(Reward);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You won %d gold!"), Reward));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold to play!"));
    }
    CloseCurrentMenu();
}

void AMerchant::CloseCurrentMenu()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromParent();
        CurrentWidget = nullptr;
        APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController)
        {
            PlayerController->SetShowMouseCursor(false);
        }
    }
    bTrading = false;
}

bool AMerchant::CheckPlayerGold(int32 Cost)
{
    AMyPaperZDCharacter *Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        return Player->SDGameInstance->GoldWealth >= Cost;
    }
    return false;
}

void AMerchant::UpdatePlayerGold(int32 Amount)
{
    AMyPaperZDCharacter *Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        Player->SDGameInstance->AddPlayerGold(Amount);
        Player->PlayerUIWidget->SetGold(Player->SDGameInstance->GoldWealth);
    }
}

int32 AMerchant::GetPlayerGold() const
{
    AMyPaperZDCharacter *Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        return Player->SDGameInstance->GoldWealth;
    }
    return 0;
}

void AMerchant::HandlePurchase(int32 ItemIndex)
{
	HandleTrade(ItemIndex, CurrentPlayer);
}

void AMerchant::HandleExit()
{
    CloseCurrentMenu();
}
