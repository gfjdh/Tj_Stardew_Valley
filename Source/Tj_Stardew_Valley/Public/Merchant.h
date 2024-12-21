#pragma once
#include "CoreMinimal.h"
#include "NPC.h"
#include "Item.h"
#include "Merchant.generated.h"

UENUM(BlueprintType)
enum class EMerchantType : uint8
{
    Vendor,   // �ۻ�����
    GameHost  // ��Ϸ����
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

    // С��Ϸ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TSubclassOf<UUserWidget> GameWidgetClass;

    // ���׽�����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TSubclassOf<UUserWidget> TradeWidgetClass;

    // ��ǰ��ʾ�Ľ���
    UPROPERTY()
    UUserWidget *CurrentWidget;

    // ��ʾ���׽���
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void ShowTradeMenu();

    // ��ʾС��Ϸ����
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void ShowGameMenu();

    // ������
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleTrade(int32 OptionIndex, AMyPaperZDCharacter *Player);

    // ����С��Ϸ
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleGame();

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
};