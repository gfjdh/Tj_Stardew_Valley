#include "MerchantWidget.h"
#include "Merchant.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMerchantWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PurchaseButton1)
    {
        PurchaseButton1->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton1Clicked);
    }

    if (PurchaseButton2)
    {
        PurchaseButton2->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton2Clicked);
    }

    if (PurchaseButton3)
    {
        PurchaseButton3->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton3Clicked);
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMerchantWidget::OnExitButtonClicked);
    }
}

void UMerchantWidget::OnPurchaseButton1Clicked()
{
    OnPurchaseButtonClicked(0);
}

void UMerchantWidget::OnPurchaseButton2Clicked()
{
    OnPurchaseButtonClicked(1);
}

void UMerchantWidget::OnPurchaseButton3Clicked()
{
    OnPurchaseButtonClicked(2);
}

void UMerchantWidget::OnPurchaseButtonClicked(int32 ItemIndex)
{
    if (CurrentMerchant)
    {
        CurrentMerchant->HandlePurchase(ItemIndex);
    }
}

void UMerchantWidget::OnExitButtonClicked()
{
    if (CurrentMerchant)
    {
        CurrentMerchant->HandleExit();
    }
}

void UMerchantWidget::SetMerchant(AMerchant *Merchant)
{
    CurrentMerchant = Merchant;

    if (CurrentMerchant)
    {
        // 设置商品图片和价格
        if (ItemImage1 && ItemPrice1)
        {
            ItemImage1->SetBrushFromTexture(CurrentMerchant->ItemsForSale[0].ItemTexture);
            ItemPrice1->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[0].Price)));
        }

        if (ItemImage2 && ItemPrice2)
        {
            ItemImage2->SetBrushFromTexture(CurrentMerchant->ItemsForSale[1].ItemTexture);
            ItemPrice2->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[1].Price)));
        }

        if (ItemImage3 && ItemPrice3)
        {
            ItemImage3->SetBrushFromTexture(CurrentMerchant->ItemsForSale[2].ItemTexture);
            ItemPrice3->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[2].Price)));
        }
    }
}
