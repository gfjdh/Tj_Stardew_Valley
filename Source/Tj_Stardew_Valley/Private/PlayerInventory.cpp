// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory()
{
	MaxInventorySlots = 20;
}

bool UPlayerInventory::AddItem(const FItemData& ItemToAdd)
{
	bool found = false;
	if (Inventory.Num() >= MaxInventorySlots)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inventory is full!"));
		return false;
	}

	FItemData* ExistingItem = nullptr;

	for (FItemData& Item : Inventory)
	{
		if (Item.ItemID == ItemToAdd.ItemID)
		{
			ExistingItem = &Item; // 修改此行
			found = true;
		}
	}

	if (found)
	{
		if (ExistingItem->CurrentAmount < ExistingItem->MaxStackAmount)
		{
			ExistingItem->CurrentAmount += ItemToAdd.CurrentAmount;
			if (ExistingItem->CurrentAmount > ExistingItem->MaxStackAmount)
			{
				ExistingItem->CurrentAmount = ExistingItem->MaxStackAmount;
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
				FString::Printf(TEXT("Added %s. New amount: %d"),
					*ItemToAdd.ItemName, ExistingItem->CurrentAmount));
			return true;
		}
	}

	Inventory.Add(ItemToAdd);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
		FString::Printf(TEXT("Added new item: %s"), *ItemToAdd.ItemName));
	return true;
}

bool UPlayerInventory::RemoveItem(int32 ItemID, int32 Amount)
{
	FItemData* Item = nullptr;

	bool found = false;

	for (FItemData& Items : Inventory)
	{
		if (Items.ItemID == ItemID)
		{
			Item = &Items; // 修改此行
			found = true;
		}
	}

	if (!found)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Item not found!"));
		return false;
	}

	if (Item->CurrentAmount < Amount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not enough items!"));
		return false;
	}

	Item->CurrentAmount -= Amount;
	if (Item->CurrentAmount <= 0)
	{
		Inventory.RemoveAll([ItemID](const FItemData& Item) { return Item.ItemID == ItemID; });
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
		FString::Printf(TEXT("Removed %d of %s"), Amount, *Item->ItemName));
	return true;
}


void UPlayerInventory::PrintInventory()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("===Inventory Contents==="));
	for (const FItemData& Item : Inventory)
	{
		if (Item.ItemID == -1)
		{
			continue;
		}
		FString ItemInfo = FString::Printf(TEXT("Item: %s (ID: %d) Amount: %d/%d"),
			*Item.ItemName, Item.ItemID, Item.CurrentAmount, Item.MaxStackAmount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
	}
}