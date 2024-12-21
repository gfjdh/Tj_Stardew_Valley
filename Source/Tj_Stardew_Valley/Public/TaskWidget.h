#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/image.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"

#include "TaskWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UTaskWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* TaskGridPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TitleText;

	bool IsOpened = false;
};
