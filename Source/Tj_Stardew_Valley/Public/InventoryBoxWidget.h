#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Inventory.h"
#include "Item.h"
#include "InventoryDragDropOperation.h"


#include "InventoryBoxWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UInventoryBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BoxImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemCounts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItem* CurrentItem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool ItemVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DoubleClickDeltaTime = 0.3f;

	float LastClickTime = 0.0f;

	int Index = -1;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateItemDisplay();

	UFUNCTION(BlueprintCallable)
	void SetItemCounts(int32 Counts);

	UFUNCTION(BlueprintCallable)
	void SetItemImage(UTexture2D* Image);

	UFUNCTION()
	void OnBoxImageClicked();

	UFUNCTION()
	void OnBoxImageDoubleClicked();

	//UFUNCTION()
	//void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

};
