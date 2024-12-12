// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up"), ItemToAdd->ItemID));
			return true;
		}
	}

	Inventory.Add(const_cast<UItem*>(ItemToAdd));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up"), ItemToAdd->ItemID));


	return true;
}


bool UInventory::RemoveItem(int32 ItemID, int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}
	for (auto& i : Inventory)
	{
		if (i->ItemID == ItemID)
		{
			if (i->CurrentAmount >= Amount)
			{
				i->CurrentAmount -= Amount;
				if (i->CurrentAmount <= 0)
				{
					Inventory.Remove(i);
				}
				return true;
			}
		}
	}
	return false;
}


void UInventory::PrintInventory()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("===Inventory Contents==="));
	for (auto& i : Inventory)
	{
		if (i->ItemID == -1)
		{
			continue;
		}
		FString ItemInfo = FString::Printf(TEXT("Item: %s (ID: %d) Amount: %d/%d"),
			*i->ItemName, i->ItemID, i->CurrentAmount, i->MaxStackAmount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, ItemInfo);
	}
}