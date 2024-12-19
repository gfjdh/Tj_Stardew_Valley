#include "BackPackWidget.h"

void UBackPackWidget::InitFlushBackPack()
{
	if (BackPackGridSlot)
	{
		BackPackGridSlot->ClearChildren();
		for (int i = 0; i < BackPackSize; i++)
		{
			UInventoryBoxWidget* InventoryBox = CreateWidget<UInventoryBoxWidget>(this, InventoryBoxClass);
			BackPackGridSlot->AddChildToGrid(InventoryBox, i / BackPackSizePerRow, i % BackPackSizePerRow);
		}
	}
}

void UBackPackWidget::EnableDisplay(bool IsVisible)
{
	if (IsVisible)
		AddToViewport();
	else
		RemoveFromParent();
}
