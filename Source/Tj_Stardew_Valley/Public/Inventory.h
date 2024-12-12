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
	int32 MaxInventorySlots = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int UsingIndex = 0;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
};
