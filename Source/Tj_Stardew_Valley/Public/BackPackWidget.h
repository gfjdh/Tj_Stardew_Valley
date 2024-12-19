#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryBoxWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Inventory.h"

#include "BackPackWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UBackPackWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	int BackPackSize = 84;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	int BackPackSizePerRow = 12;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackPackBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* BackPackGridSlot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryBoxWidget> InventoryBoxClass;

	int IsOpen = false;
public:
	UFUNCTION(BlueprintCallable)
	void InitFlushBackpack();

	UFUNCTION(BlueprintCallable)
	void FlushBackpack(UInventory* Inventory);

	UFUNCTION(BlueprintCallable)
	void EnableDisplay(bool IsVisible);

	UFUNCTION()
	void OnExitButtonClicked();
};
