#include "BackPackWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBackPackWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UBackPackWidget::OnExitButtonClicked);
	InitFlushBackpack();
}

void UBackPackWidget::InitFlushBackpack()
{
	if (BackPackGridSlot)
	{
		BackPackGridSlot->ClearChildren();
		for (int i = 0; i < BackPackSize; i++)
		{
			UInventoryBoxWidget* InventoryBox = CreateWidget<UInventoryBoxWidget>(this, InventoryBoxClass);
			InventoryBox->FlushBackpackDelegate.AddDynamic(this, &UBackPackWidget::FlushBackpack);
			InventoryBox->Index = i;
			BackPackGridSlot->AddChildToGrid(InventoryBox, i / BackPackSizePerRow, i % BackPackSizePerRow);
			InventoryBox->UpdateItemDisplay();
		}
	}
}

void UBackPackWidget::FlushBackpack(UInventory* Inventory)
{
	if (BackPackGridSlot)
	{
		for (int i = 0; i < BackPackSize; i++)
		{
			UInventoryBoxWidget* InventoryBox = Cast<UInventoryBoxWidget>(BackPackGridSlot->GetChildAt(i));
			if (InventoryBox)
			{
				if (Inventory->Inventory.Num() > i)//不越界时
				{
					InventoryBox->CurrentItem = (Inventory->Inventory)[i];
					InventoryBox->SetItemImage(Inventory->Inventory[i]->ItemTexture);
					InventoryBox->SetItemCounts(Inventory->Inventory[i]->CurrentAmount);
				}
				else//越界时(背包物品全部显示完毕,剩下格子用空格渲染)
				{
					InventoryBox->CurrentItem = nullptr;
					InventoryBox->SetItemImage(nullptr);
					InventoryBox->SetItemCounts(0);
				}
				InventoryBox->UpdateItemDisplay();
			}
		}
	}
}

void UBackPackWidget::EnableDisplay(bool IsVisible)
{
	if (IsVisible) {
		AddToViewport();
		UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
	}
	else
		RemoveFromParent();
}

void UBackPackWidget::OnExitButtonClicked()
{
	IsOpen = false;
	EnableDisplay(false);

	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
	if (PlayerActor) {
		AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
		Player->ActivatePlayer(true);
		Player->CurrentPlayerState = EPlayerState::Idle;
	}
}