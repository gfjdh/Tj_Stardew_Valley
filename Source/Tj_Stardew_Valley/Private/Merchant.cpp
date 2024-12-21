#include "Merchant.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MerchantWidget.h"

AMerchant::AMerchant()
{
    // 设置商人不需要移动
    PrimaryActorTick.bCanEverTick = false;

    // 设置商人碰撞体积
    NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

    // 设置商人待机动画
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleAnimation(TEXT("/Game/Animations/IdleAnimation"));
    if (IdleAnimation.Succeeded())
    {
        NPCFlipbookComponent->SetFlipbook(IdleAnimation.Object);
    }

    // 初始化商人类型
    MerchantType = EMerchantType::Vendor;

    // 初始化交易选项
    TradeOptions.Add(TEXT("Buy Health Potion (10 Gold)"));
    TradeOptions.Add(TEXT("Buy Mana Potion (15 Gold)"));
    TradeOptions.Add(TEXT("Buy Sword (50 Gold)"));

    // 初始化小游戏界面类
    static ConstructorHelpers::FClassFinder<UUserWidget> GameWidget(TEXT("/Game/BluePrints/NPC/GameWidget"));
    if (GameWidget.Succeeded())
    {
        GameWidgetClass = GameWidget.Class;
    }

    // 初始化交易界面类
    static ConstructorHelpers::FClassFinder<UUserWidget> TradeWidget(TEXT("/Game/BluePrints/NPC/TradeWidget"));
    if (TradeWidget.Succeeded())
    {
        TradeWidgetClass = TradeWidget.Class;
    }

    // 初始化商品数据
    ItemsForSale.Add({ nullptr, 10 }); // Health Potion
    ItemsForSale.Add({ nullptr, 15 }); // Mana Potion
    ItemsForSale.Add({ nullptr, 50 }); // Sword
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
}

void AMerchant::ShowTradeMenu()
{
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
            }
        }
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

void AMerchant::HandleTrade(int32 OptionIndex)
{
    if (OptionIndex >= 0 && OptionIndex < TradeOptions.Num())
    {
        FString Option = TradeOptions[OptionIndex];
        if (Option.Contains(TEXT("Health Potion")))
        {
            if (CheckPlayerGold(10))
            {
                UpdatePlayerGold(-10);
                // 给玩家添加物品
                // PlayerInventory->AddItem(HealthPotionItem);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You bought a Health Potion!"));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
            }
        }
        else if (Option.Contains(TEXT("Mana Potion")))
        {
            if (CheckPlayerGold(15))
            {
                UpdatePlayerGold(-15);
                // 给玩家添加物品
                // PlayerInventory->AddItem(ManaPotionItem);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You bought a Mana Potion!"));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
            }
        }
        else if (Option.Contains(TEXT("Sword")))
        {
            if (CheckPlayerGold(50))
            {
                UpdatePlayerGold(-50);
                // 给玩家添加物品
                // PlayerInventory->AddItem(SwordItem);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You bought a Sword!"));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
            }
        }
    }
    CloseCurrentMenu();
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
        Player->SDGameInstance->SetPlayerGold(Player->SDGameInstance->GoldWealth + Amount);
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
    if (ItemIndex >= 0 && ItemIndex < ItemsForSale.Num())
    {
        int32 ItemPrice = ItemsForSale[ItemIndex].Price;
        if (CheckPlayerGold(ItemPrice))
        {
            UpdatePlayerGold(-ItemPrice);
            // 给玩家添加物品
            // PlayerInventory->AddItem(ItemsForSale[ItemIndex].Item);
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Purchase successful!"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
        }
    }
}

void AMerchant::HandleExit()
{
    CloseCurrentMenu();
}
