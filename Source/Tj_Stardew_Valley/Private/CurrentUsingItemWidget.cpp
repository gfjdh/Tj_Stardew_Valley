#include "CurrentUsingItemWidget.h"

void UCurrentUsingItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitInventoryBox();
}

void UCurrentUsingItemWidget::FlushSlot(UInventory* Inventory)
{
	//��ʾ��ǰʹ�õ���Ʒ
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
	//��sizebox�д���InventoryBox
	InventoryBox = CreateWidget<UInventoryBoxWidget>(this, InventoryBoxClass);
	if (InventoryBox) {
		//��ֹhover�͵�����¼�
		InventoryBox->SetIsEnabled(false);
		//����Ϊsizebox��child
		InventoryBoxSizeBox->AddChild(InventoryBox);
		InventoryBox->SetItemImage(nullptr);
		InventoryBox->SetItemCounts(0);
		InventoryBox->UpdateItemDisplay();
	}
}
