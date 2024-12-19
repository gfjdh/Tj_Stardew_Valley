#include "InventoryBoxWidget.h"

void UInventoryBoxWidget::UpdateItemDisplay()
{
	//ÏÔÊ¾»òÒþ²ØItemImage
	if (ItemVisible) {
		ItemImage->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventoryBoxWidget::SetItemCounts(int32 Counts)
{
	CurrentItemCounts = Counts;
	if (CurrentItemCounts >= 2) {
		ItemCounts->SetText(FText::FromString(FString::FromInt(CurrentItemCounts)));
	}
	else {
		ItemCounts->SetText(FText::FromString(""));
	}

	if (CurrentItemCounts > 0)
	{
		ItemVisible = true;
	}
	else
	{
		ItemVisible = false;
	}
}

void UInventoryBoxWidget::SetItemImage(UTexture2D* Image)
{
}

void UInventoryBoxWidget::OnSelected()
{
}
