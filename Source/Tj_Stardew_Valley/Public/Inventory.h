// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"

#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TJ_STARDEW_VALLEY_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItem*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxInventorySlots = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> InventoryPosition;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 添加物品
	UFUNCTION()
	bool AddItem(const UItem* ItemToAdd);

	// 移除物品
	UFUNCTION()
	bool RemoveItem(int32 ItemID, int32 Amount);

	// 打印物品栏内容(Debug用)
	UFUNCTION()
	void PrintInventory();
};
