#include "Merchant.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MerchantWidget.h"

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
    // �������˴�������
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleAnimation(TEXT("/Game/Animations/IdleAnimation"));
    if (IdleAnimation.Succeeded())
    {
        NPCFlipbookComponent->SetFlipbook(IdleAnimation.Object);
    }

    // ��ʼ����������
    MerchantType = EMerchantType::Vendor;

    // ��ʼ������ѡ��
    TradeOptions.Add(TEXT("Buy woods (10 Gold)"));
    TradeOptions.Add(TEXT("Buy apples (15 Gold)"));
    TradeOptions.Add(TEXT("Buy rings (50 Gold)"));

    // ��ʼ��С��Ϸ������
    static ConstructorHelpers::FClassFinder<UUserWidget> GameWidget(TEXT("/Game/BluePrints/NPC/BP_GameWidget"));
    if (GameWidget.Succeeded())
    {
        GameWidgetClass = GameWidget.Class;
    }

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

    // ��ʼ���Ի�����
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
// ��ȡNPC����ײ��
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
            // ����������Ʒ
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
        // ��ʼС��Ϸ
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game started!"));
        // С��Ϸ�߼�
        // ...
        // �������Ӯ��
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
