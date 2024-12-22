#include "Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
}

void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::HasItem(int32 ItemID) const
{
	for (UItem *Item : Inventory)
	{
		if (Item && Item->ItemID == ItemID)
		{
			return true;
		}
	}
	return false;
}

bool UInventory::AddItem(const UItem* ItemToAdd)
{
	if (ItemToAdd == nullptr)
	{
		return false;
	}
	if (Inventory.Num() >= MaxInventorySlots)
	{
		return false;
	}
	if (ItemToAdd->MaxStackAmount <= 0)
	{
		return false;
	}
	if (ItemToAdd->CurrentAmount > ItemToAdd->MaxStackAmount)
	{
		return false;
	}
	for (auto& i : Inventory)
	{
		if (i->ItemID == ItemToAdd->ItemID)
		{
			i->CurrentAmount += 1;
			return true;
		}
	}

	Inventory.Add(const_cast<UItem*>(ItemToAdd));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up"), ItemToAdd->ItemID));


	return true;
}

bool UInventory::AddItemByIndex(const UItem* ItemToAdd)
{
	if (ItemToAdd == nullptr)
	{
		return false;
	}
	if (Inventory.Num() >= MaxInventorySlots)
	{
		return false;
	}
	if (ItemToAdd->CurrentAmount <= 0)
	{
		return false;
	}
	if (ItemToAdd->MaxStackAmount <= 0)
	{
		return false;
	}
	if (ItemToAdd->CurrentAmount > ItemToAdd->MaxStackAmount)
	{
		return false;
	}
	for (auto& i : Inventory)
	{
		if (i->ItemID == ItemToAdd->ItemID)
		{
			i->CurrentAmount += ItemToAdd->CurrentAmount;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up"), ItemToAdd->ItemID));
			return true;
		}
	}
	Inventory.Add(const_cast<UItem*>(ItemToAdd));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up"), ItemToAdd->ItemID));
	return true;
}


bool UInventory::RemoveItem(int32 ItemID, int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}
	for (int32 Index = 0; Index < Inventory.Num(); ++Index)
	{
		if (Inventory[Index]->ItemID == ItemID)
		{
			return RemoveItemByIndex(Index, Amount);
		}
	}
	return false;
}

bool UInventory::RemoveItemByIndex(int32 Index, int32 Amount) {
	if (Amount <= 0)
	{
		return false;
	}
	if (Index < 0 || Index >= Inventory.Num())
	{
		return false;
	}
	if (Inventory[Index]->CurrentAmount >= Amount)
	{
		Inventory[Index]->CurrentAmount -= Amount;
		if (Inventory[Index]->CurrentAmount <= 0)
		{
			Inventory.RemoveAt(Index);
			if (Index == UsingIndex) {
				UsingIndex = 0;
			}
		}
		return true;
	}
	return false;
}

void UInventory::PrintInventory()
{
	int Index = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("===Inventory Contents==="));
	for (auto& i : Inventory)
	{
		if (i->ItemID == -1)
		{
			continue;
		}
		FString ItemInfo = FString::Printf(TEXT("Item: %s (ID: %d) Amount: %d/%d,Index:%d"),
			*i->ItemName, i->ItemID, i->CurrentAmount, i->MaxStackAmount,Index);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
		Index++;
	}
}

// 使用物品
UItem* UInventory::UseItem()
{
	if (Inventory.Num() <= 0)
	{
		return nullptr;
	}
	if (UsingIndex >= Inventory.Num())
	{
		UsingIndex = 0;
	}
	if (Inventory[UsingIndex]->ItemID == -1)
	{
		return nullptr;
	}
	if (Inventory[UsingIndex]->bIsConsumable)
	{
		FString ItemInfo = FString::Printf(TEXT("Using :%d"), Inventory[UsingIndex]->ItemID);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
		return Inventory[UsingIndex];
	}
	if (Inventory[UsingIndex]->bIsEquippable)
	{
		FString ItemInfo = FString::Printf(TEXT("Equipping :%d"), Inventory[UsingIndex]->ItemID);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
		return Inventory[UsingIndex];
	}
	return nullptr;
}

// 改变使用物品的序号
void UInventory::SwitchItem()
{
	UsingIndex++;
	if (UsingIndex >= Inventory.Num())
	{
		UsingIndex = 0;
	}
	if (Inventory.Num() <= 0) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Inventory Empty"));
	}
	else {
		FString ItemInfo = FString::Printf(TEXT("Switching to :%s"), *Inventory[UsingIndex]->ItemName);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
	}
}
