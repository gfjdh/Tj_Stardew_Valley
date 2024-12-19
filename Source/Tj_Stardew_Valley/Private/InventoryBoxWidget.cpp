#include "InventoryBoxWidget.h"
#include "Inventory.h"

void UInventoryBoxWidget::UpdateItemDisplay()
{
	//ÏÔÊ¾»òÒş²ØItemImage
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
	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(Image);
	}
}

UTexture2D* UInventoryBoxWidget::GetItemImage(int index)
{
	if (Inventory) {
		if (Inventory->Inventory[index]) {
			UPaperSprite* CurrentSprite = Inventory->Inventory[index]->ItemSprite;
			if (CurrentSprite) {
				return CurrentSprite->GetBakedTexture();
			}
		}
	}
	return nullptr;
}

int32 UInventoryBoxWidget::GetItemCounts(int index)
{
	if (Inventory) {
		if (Inventory->Inventory[index]) {
			return Inventory->Inventory[index]->CurrentAmount;
		}
	}
	return 0;
}
