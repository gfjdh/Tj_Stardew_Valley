// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PaperSprite.h"

#include "PlayerInventory.generated.h"

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
struct FItemData
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

	FItemData()
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
	FItemData(int32 ID, FString Name, CollectableType Type, UPaperSprite* Sprite, int32 Amount, int32 MaxAmount, bool Consumable, bool Equippable)
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
};

UCLASS(Blueprintable)
class TJ_STARDEW_VALLEY_API UPlayerInventory : public UObject
{
	GENERATED_BODY()

public:
	UPlayerInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemData> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxInventorySlots;

	// 添加物品
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(const FItemData& ItemToAdd);

	// 移除物品
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(int32 ItemID, int32 Amount);

	// 打印物品栏内容(Debug用)
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PrintInventory();
};
