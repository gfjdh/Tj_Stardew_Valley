#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "Merchant.generated.h"

UENUM(BlueprintType)
enum class EMerchantType : uint8
{
    Vendor,   // 售货商人
    GameHost  // 游戏商人
};

USTRUCT(BlueprintType)
struct FItemForSale
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D *ItemTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Price;

    FItemForSale()
        : ItemTexture(nullptr), Price(0)
    {
    }

    FItemForSale(UTexture2D *InItem, int32 InPrice)
        : ItemTexture(InItem), Price(InPrice)
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


	// 商品数据
    void HandlePurchase(int32 ItemIndex);
	// 退出交易
    void HandleExit();
    // 商人类型
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    EMerchantType MerchantType;

    // 交易选项
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TArray<FString> TradeOptions;

    // 小游戏界面类
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TSubclassOf<UUserWidget> GameWidgetClass;

    // 交易界面类
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TSubclassOf<UUserWidget> TradeWidgetClass;

    // 当前显示的界面
    UPROPERTY()
    UUserWidget *CurrentWidget;

    // 显示交易界面
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void ShowTradeMenu();

    // 显示小游戏界面
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void ShowGameMenu();

    // 处理交易
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleTrade(int32 OptionIndex);

    // 处理小游戏
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void HandleGame();

    // 关闭当前界面
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void CloseCurrentMenu();

    // 检查玩家金币是否足够
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    bool CheckPlayerGold(int32 Cost);

    // 更新玩家金币
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    void UpdatePlayerGold(int32 Amount);

    // 获取玩家金币
    UFUNCTION(BlueprintCallable, Category = "Merchant")
    int32 GetPlayerGold() const;

    // 商品列表
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
    TArray<FItemForSale> ItemsForSale;
};