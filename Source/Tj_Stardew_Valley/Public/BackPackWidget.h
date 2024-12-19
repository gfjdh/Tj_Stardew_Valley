#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryBoxWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"

#include "BackPackWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UBackPackWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	int BackPackSize = 60;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	int BackPackSizePerRow = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackPackBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* BackPackGridSlot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryBoxWidget> InventoryBoxClass;
public:
	UFUNCTION(BlueprintCallable)
	void InitFlushBackPack();
};
