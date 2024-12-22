#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "SlateCore.h"
#include "MerchantWidget.generated.h"

class AMerchant;
class UButton;
class UTextBlock;

UCLASS()
class TJ_STARDEW_VALLEY_API UMerchantWidget : public UUserWidget
{
    GENERATED_BODY()


public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnPurchaseButtonClicked(int32 ItemIndex);

    UFUNCTION()
    void OnExitButtonClicked();

    void SetMerchant(AMerchant *Merchant);

    UFUNCTION()
    void OnPurchaseButton1Clicked();

    UFUNCTION()
    void OnPurchaseButton2Clicked();

    UFUNCTION()
    void OnPurchaseButton3Clicked();
protected:
    UPROPERTY(meta = (BindWidget))
    UButton *PurchaseButton1;

    UPROPERTY(meta = (BindWidget))
    UButton *PurchaseButton2;

    UPROPERTY(meta = (BindWidget))
    UButton *PurchaseButton3;

    UPROPERTY(meta = (BindWidget))
    UButton *ExitButton;

    UPROPERTY(meta = (BindWidget))
    UImage *ItemImage1;

    UPROPERTY(meta = (BindWidget))
    UImage *ItemImage2;

    UPROPERTY(meta = (BindWidget))
    UImage *ItemImage3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *ItemPrice1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *ItemPrice2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *ItemPrice3;

private:
    AMerchant *CurrentMerchant;
};