#include "CurrentUsingItemWidget.h"

void UCurrentUsingItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitInventoryBox();
}

void UCurrentUsingItemWidget::FlushSlot(UInventory* Inventory)
{
	//显示当前使用的物品
	if (Inventory && InventoryBox) {
		int CurrentIndex = Inventory->UsingIndex;
		if (Inventory->Inventory.Num() > CurrentIndex) {
			InventoryBox->CurrentItem = Inventory->Inventory[CurrentIndex];
			InventoryBox->SetItemImage(Inventory->Inventory[CurrentIndex]->ItemTexture);
			InventoryBox->SetItemCounts(Inventory->Inventory[CurrentIndex]->CurrentAmount);
			InventoryBox->UpdateItemDisplay();
		}
		else {
			InventoryBox->CurrentItem = nullptr;
			InventoryBox->SetItemImage(nullptr);
			InventoryBox->SetItemCounts(0);
			InventoryBox->UpdateItemDisplay();
		}
	}
}

void UCurrentUsingItemWidget::InitInventoryBox()
{
	//在sizebox中创建InventoryBox
	InventoryBox = CreateWidget<UInventoryBoxWidget>(this, InventoryBoxClass);
	if (InventoryBox) {
		//禁止hover和点击等事件
		InventoryBox->SetIsEnabled(false);
		//设置为sizebox的child
		InventoryBoxSizeBox->AddChild(InventoryBox);
		InventoryBox->SetItemImage(nullptr);
		InventoryBox->SetItemCounts(0);
		InventoryBox->UpdateItemDisplay();
	}
}
