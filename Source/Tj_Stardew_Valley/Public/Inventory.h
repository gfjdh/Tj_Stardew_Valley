// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Crop.h"

#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TJ_STARDEW_VALLEY_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UItem *> Inventory;//��Ʒ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxInventorySlots = 40;//�����Ʒ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UsingIndex = 0;//��ǰʹ����Ʒ�����


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ����Ƿ���ָ��ID����Ʒ
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(int32 ItemID) const;

	// �����Ʒ
	UFUNCTION()
	bool AddItem(const UItem* ItemToAdd);

	bool AddItemByIndex(const UItem* ItemToAdd);
	// �Ƴ���Ʒ
	UFUNCTION()
	bool RemoveItem(int32 ItemID, int32 Amount);

	UFUNCTION()
	bool RemoveItemByIndex(int32 Index, int32 Amount);

	// ��ӡ��Ʒ������(Debug��)
	UFUNCTION()
	void PrintInventory();

	// ʹ����Ʒ
	UFUNCTION()
	UItem* UseItem();

	// �ı�ʹ����Ʒ�����
	UFUNCTION()
	void SwitchItem();

	UFUNCTION()
	UItem* CurrentItem() { return Inventory[UsingIndex]; }
};
