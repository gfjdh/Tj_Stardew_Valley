#pragma once
#include "CoreMinimal.h"
#include "NPC.h"
#include "Item.h"
#include "Merchant.generated.h"

UENUM(BlueprintType)
enum class EMerchantType : uint8
{
    Vendor,   // �ۻ�����
	Buyer    // �ջ�����
};

USTRUCT(BlueprintType)
struct FItemForSale
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemData FItemData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Price;

    FItemForSale()
        : FItemData(), Price(0)
    {
    }

    FItemForSale(int32 InPrice)
        : FItemData(), Price(InPrice)
    {
    }
};

UCLASS()
class TJ_STARDEW_VALLEY_API AMerchant : public ANPC
{
    GENERATED_BODY()

public:
    AMerchant();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UBoxComponent *GetPlayerInteractionBox(AMyPaperZDCharacter *Player);
    // �������Ƿ񿿽��������Ի�
    virtual void CheckForPlayerInteractionBox() override;

	// ��Ʒ����
    void HandlePurchase(int32 ItemIndex);
	// ������Ʒ
    TSubclassOf<ACollectableEntity> GetCollectableEntityClass(int32 Index);
	// �˳�����
    void HandleExit();

    UCapsuleComponent *AMerchantCapsuleComponent;
    // ��������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    EMerchantType MerchantType;

    // ����ѡ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TArray<FString> TradeOptions;

    // ���׽�����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TSubclassOf<UUserWidget> TradeWidgetClass;

    // ��ǰ��ʾ�Ľ���
    UPROPERTY()
    UUserWidget *CurrentWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    ACGameMode* GameMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    int SellWeight = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    int BuyWeight = 1;

    // ��ʾ���׽���
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void ShowTradeMenu();

    // ������
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleTrade(int32 OptionIndex, AMyPaperZDCharacter *Player);

    // ��������
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleSale(int32 OptionIndex, AMyPaperZDCharacter *Player);

    // �رյ�ǰ����
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void CloseCurrentMenu();

    // �����ҽ���Ƿ��㹻
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    bool CheckPlayerGold(int32 Cost);

    // ������ҽ��
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void UpdatePlayerGold(int32 Amount);

    // ��ȡ��ҽ��
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    int32 GetPlayerGold() const;

    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void UpdatePrice();

    // ��Ʒ�б�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TArray<FItemForSale> ItemsForSale;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ACollectableEntity> CollectableEntityClass1;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ACollectableEntity> CollectableEntityClass2;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ACollectableEntity> CollectableEntityClass3;

private:
	AMyPaperZDCharacter *CurrentPlayer = nullptr;
	bool bTrading = false;
};