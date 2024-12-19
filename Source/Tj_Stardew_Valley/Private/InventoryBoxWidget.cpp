#include "InventoryBoxWidget.h"
#include "Inventory.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UInventoryBoxWidget::UpdateItemDisplay()
{
	//ÏÔÊ¾»òÒþ²ØItemImage
	if (ItemVisible) {
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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