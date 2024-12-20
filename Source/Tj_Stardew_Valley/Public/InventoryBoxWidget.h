#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Inventory.h"
#include "Item.h"
#include "SlateCore.h"


#include "InventoryBoxWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UInventoryBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* Canvas;

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

	void SwapItem(int DragIndex);
};
