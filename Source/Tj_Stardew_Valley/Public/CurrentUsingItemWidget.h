#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryBoxWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

#include "Inventory.h"

#include "CurrentUsingItemWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UCurrentUsingItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* DisplayBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* InventoryBoxSizeBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryBoxWidget> InventoryBoxClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HintText;

	UInventoryBoxWidget* InventoryBox;
public:
	UFUNCTION(BlueprintCallable)
	void FlushSlot(UInventory* Inventory);


	UFUNCTION()
	void InitInventoryBox();
};
