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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton1 ok"));
        PurchaseButton1->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton1Clicked);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton1 is null!"));
    }
    if (PurchaseButton2)
    {
        PurchaseButton2->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton2Clicked);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton2 is null!"));
    }
    if (PurchaseButton3)
    {
        PurchaseButton3->OnClicked.AddDynamic(this, &UMerchantWidget::OnPurchaseButton3Clicked);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton3 is null!"));
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMerchantWidget::OnExitButtonClicked);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton1 is null!"));
    }
}

void UMerchantWidget::OnPurchaseButton1Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PurchaseButton1Clicked!"));
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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HandlePurchase!"));
    }
    else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CurrentMerchant is null!"));
	}
}

void UMerchantWidget::OnExitButtonClicked()
{
    if (CurrentMerchant)
    {
        CurrentMerchant->HandleExit();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CurrentMerchant is null!"));
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
            ItemImage1->SetBrushFromTexture(CurrentMerchant->ItemsForSale[0].FItemData.ItemTexture);
            ItemPrice1->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[0].Price)));
        }

        if (ItemImage2 && ItemPrice2)
        {
            ItemImage2->SetBrushFromTexture(CurrentMerchant->ItemsForSale[1].FItemData.ItemTexture);
            ItemPrice2->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[1].Price)));
        }

        if (ItemImage3 && ItemPrice3)
        {
            ItemImage3->SetBrushFromTexture(CurrentMerchant->ItemsForSale[2].FItemData.ItemTexture);
            ItemPrice3->SetText(FText::FromString(FString::FromInt(CurrentMerchant->ItemsForSale[2].Price)));
        }
    }
}
