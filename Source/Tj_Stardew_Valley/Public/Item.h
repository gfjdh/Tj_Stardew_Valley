// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PaperSprite.h"
#include "Engine/DataTable.h"


#include "Item.generated.h"



UENUM(BlueprintType)
enum class CollectableType : uint8
{
	None,
	Potion,
	Gold,
	Wood,
	Stone,
	Ore,
	Seed,
	Tool,
	Food,
	Crop,
	Other
};
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CollectableType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* ItemSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquippable;
};



/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CollectableType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* ItemSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConsumable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquippable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemDataTable;

	UItem()
	{
		ItemID = -1;
		ItemName = TEXT("None");
		ItemType = CollectableType::None;
		ItemSprite = nullptr;
		CurrentAmount = 0;
		MaxStackAmount = 99;
		bIsConsumable = false;
		bIsEquippable = false;
	}
	UItem(int32 ID, FString Name, CollectableType Type, UPaperSprite* Sprite, int32 Amount, int32 MaxAmount, bool Consumable, bool Equippable)
	{
		ItemID = ID;
		ItemName = Name;
		ItemType = Type;
		ItemSprite = Sprite;
		CurrentAmount = Amount;
		MaxStackAmount = MaxAmount;
		bIsConsumable = Consumable;
		bIsEquippable = Equippable;
	}

	void CreateItemInfo(int32 InItemID);

	void ConsumeItem();

	void EquipItem();

	void UnEquipItem();

	void DropItem();
};
