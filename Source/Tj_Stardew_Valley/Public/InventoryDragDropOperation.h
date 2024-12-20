#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryBoxWidget.h"

#include "InventoryDragDropOperation.generated.h"


UCLASS()
class TJ_STARDEW_VALLEY_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UInventoryDragDropOperation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
	UObject* BoxPayload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
	UInventoryBoxWidget* DraggedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
	int32 DraggedIndex = -1;
};

