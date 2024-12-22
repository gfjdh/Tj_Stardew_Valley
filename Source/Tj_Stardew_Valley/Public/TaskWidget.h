#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "TaskItemWidget.h"

#include "TaskWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UTaskWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* TaskGridPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTaskItemWidget> TaskItemWidgetClass;

	bool IsOpened = false;

	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void ShowCurrentTasks(AActor* PlayerActor);

	UFUNCTION()
	void CloseTaskWidget();
};
