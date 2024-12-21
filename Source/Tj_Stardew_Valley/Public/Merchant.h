#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "Merchant.generated.h"

UENUM(BlueprintType)
enum class EMerchantType : uint8
{
    Vendor,   // �ۻ�����
    GameHost  // ��Ϸ����
};

UCLASS()
class TJ_STARDEW_VALLEY_API AMerchant : public ANPC
{
    GENERATED_BODY()

public:
    AMerchant();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

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
    void HandleTrade(int32 OptionIndex);

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
};