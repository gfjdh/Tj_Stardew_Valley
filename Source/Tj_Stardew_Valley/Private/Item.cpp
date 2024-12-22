// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
    ItemID = -1;
    ItemName = TEXT("None");
    ItemType = CollectableType::None;
    ItemSprite = nullptr;
    ItemTexture = nullptr;
    CurrentAmount = 0;
    MaxStackAmount = 99;
    bIsConsumable = false;
    bIsEquippable = false;
}


void UItem::CreateItemInfo(int32 InItemID)
{
    static const FString ContextString(TEXT("Item Data Context"));
	ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Engine.DataTable'/Game/Inventory/Item_Table.Item_Table'"));
    if (ItemDataTable)
    {
        FString LocalContextString;
        FName ItemRowName = FName(*FString::FromInt(InItemID));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d Picked Up5"), InItemID));
        FItemData* ItemData = ItemDataTable->FindRow<FItemData>(ItemRowName, LocalContextString);

        if (ItemData)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("if")));
            ItemID = ItemData->ItemID;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item ID %d"), ItemID));
            ItemName = ItemData->ItemName;
            ItemType = ItemData->ItemType;
            ItemSprite = ItemData->ItemSprite;
			ItemTexture = ItemData->ItemTexture;
            MaxStackAmount = ItemData->MaxStackAmount;
            CurrentAmount = ItemData->CurrentAmount;
            bIsConsumable = ItemData->bIsConsumable;
            bIsEquippable = ItemData->bIsEquippable;
            /*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                FString::Printf(TEXT("Item ID %d found in DataTable"), InItemID));*/
        }
        else
        {
            /*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                FString::Printf(TEXT("Item ID %d not found in DataTable"), InItemID));*/
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("Failed to load Item DataTable"));
    }
}



