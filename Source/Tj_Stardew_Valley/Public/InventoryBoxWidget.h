#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Inventory.h"

#include "InventoryBoxWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UInventoryBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BoxImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemCounts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentItemCounts = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool ItemVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventory* Inventory;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateItemDisplay();

	UFUNCTION(BlueprintCallable)
	void SetItemCounts(int32 Counts);

	UFUNCTION(BlueprintCallable)
	void SetItemImage(UTexture2D* Image);
};
