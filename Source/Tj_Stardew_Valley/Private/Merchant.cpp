#include "Merchant.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MerchantWidget.h"
#include "Inventory.h"


AMerchant::AMerchant()
{
    // �������˲���Ҫ�ƶ�
    PrimaryActorTick.bCanEverTick = true;
    // ����������ײ���
    NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    // ����NPC���ƶ�����
    MovementAreaCenter = FVector(0.0f, -180.0f, 10.0f); // ����NPC���ƶ���������
    MovementAreaRadius = 0.0f; // ����NPC���ƶ�����뾶
    MovementSpeed = 0.0f; // ����NPC���ƶ��ٶ�
    CurrentDirection = FVector::ZeroVector; // ��ʼ��NPC�ķ���
    TimeToChangeDirection = 0.0f; // ��ʼ��ʱ��

    // ��ʼ����������
    MerchantType = EMerchantType::Vendor;

    // ��ʼ������ѡ��
    TradeOptions.Add(TEXT("Buy woods (10 Gold)"));
    TradeOptions.Add(TEXT("Buy apples (15 Gold)"));
    TradeOptions.Add(TEXT("Buy rings (50 Gold)"));

    // ��ʼ�����׽�����
    static ConstructorHelpers::FClassFinder<UUserWidget> TradeWidget(TEXT("/Game/BluePrints/NPC/BP_TradeWidget"));
    if (TradeWidget.Succeeded())
    {
        TradeWidgetClass = TradeWidget.Class;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to find TradeWidget class!"));
    }
    // ��ʼ����Ʒ����
    ItemsForSale.Add(10);
    ItemsForSale.Add(15);
    ItemsForSale.Add(50);

    CurrentPlayer = nullptr;
    bTrading = false;
}

void AMerchant::BeginPlay()
{
    Super::BeginPlay();
    MGameMode = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());
}

void AMerchant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bTrading)
    {
        AMerchant::CheckForPlayerInteractionBox();
    }

    UpdatePrice();
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
            }
        }
    }
}

// ��ȡ��ײ��
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

void AMerchant::UpdatePrice() {
    switch (MGameMode->CurrentSeason) {
        case ESeason::Spring:
            SellWeight = 2;
            BuyWeight = 1;
            break;
        case ESeason::Summer:
            SellWeight = 1;
            BuyWeight = 2;
            break;
        case ESeason::Fall:
            SellWeight = 2;
            BuyWeight = 2;
            break;
        case ESeason::Winter:
            SellWeight = 1;
            BuyWeight = 3;
            break;
        default:
            break;
    }
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
            // ��ȡ��ҵĻ�����ײ��
            UBoxComponent *InteractionBox = GetPlayerInteractionBox(Player);
            if (InteractionBox && InteractionBox->IsOverlappingActor(this)) {
                CurrentPlayer = Player;
                //���������Ϣ
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ShowGameMenu!"));
                ShowTradeMenu();
                bPlayerNearby = true;
                DialogueCooldown = 3.0f; // ������ȴʱ��Ϊ3��
            }
        }
    }
}

void AMerchant::HandleTrade(int32 OptionIndex, AMyPaperZDCharacter *Player)
{
    if (OptionIndex >= 0 && OptionIndex < ItemsForSale.Num())
    {
        FItemForSale Option = ItemsForSale[OptionIndex];
		if (CheckPlayerGold(ItemsForSale[OptionIndex].Price))
        {
            if (Player->PlayerSkill->Farming->SkillStage > 2||Option.FItemData.ItemID!=1003) {
                UpdatePlayerGold(-1 * ItemsForSale[OptionIndex].Price * SellWeight);
                // ����������Ʒ
                SpawnItemForPlayer(Player, GetCollectableEntityClass(OptionIndex));
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You bought a Item!"));
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough gold!"));
        }
    }
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

void AMerchant::HandleSale(int32 OptionIndex, AMyPaperZDCharacter *Player)
{
    if (OptionIndex >= 0 && OptionIndex < ItemsForSale.Num())
    {
        FItemForSale Option = ItemsForSale[OptionIndex];
        UInventory *PlayerInventory = Player->FindComponentByClass<UInventory>();

        if (PlayerInventory && PlayerInventory->HasItem(Option.FItemData.ItemID))
        {
            // �Ƴ���ҵ���Ʒ
            PlayerInventory->RemoveItem(Option.FItemData.ItemID, 1);
            // ������ҵĽ��
            UpdatePlayerGold(Option.Price * BuyWeight);
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Item sold!"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You don't have the item to sell!"));
        }
    }
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
	if (MerchantType == EMerchantType::Vendor)
	{
		HandleTrade(ItemIndex, CurrentPlayer);
	}
	else if (MerchantType == EMerchantType::Buyer)
	{
        HandleSale(ItemIndex, CurrentPlayer);
	}
}

void AMerchant::HandleExit()
{
    CloseCurrentMenu();
}
