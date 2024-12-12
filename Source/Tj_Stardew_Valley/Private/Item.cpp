// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"




void UItem::CreateItemInfo(int32 InItemID)
{
    static const FString ContextString(TEXT("Item Data Context"));
    ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Inventory/Item_Table.Item_Table'"));

    if (ItemDataTable)
    {
        FString LocalContextString;
        FName ItemRowName = FName(*FString::FromInt(InItemID));
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
            //FString::Printf(TEXT("Looking for Item ID %d with RowName %s"), InItemID, *ItemRowName.ToString()));

        FItemData* ItemData = ItemDataTable->FindRow<FItemData>(ItemRowName, LocalContextString);

        if (ItemData)
        {
            ItemID = ItemData->ItemID;
            ItemName = ItemData->ItemName;
            ItemType = ItemData->ItemType;
            ItemSprite = ItemData->ItemSprite;
            MaxStackAmount = ItemData->MaxStackAmount;
            CurrentAmount = ItemData->CurrentAmount;
            bIsConsumable = ItemData->bIsConsumable;
            bIsEquippable = ItemData->bIsEquippable;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                FString::Printf(TEXT("Item ID %d found in DataTable"), InItemID));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                FString::Printf(TEXT("Item ID %d not found in DataTable"), InItemID));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
            TEXT("Failed to load Item DataTable"));
    }
}


void UItem::ConsumeItem()
{

}

void UItem::EquipItem()
{
}

void UItem::UnEquipItem()
{
}

void UItem::DropItem()
{
}

