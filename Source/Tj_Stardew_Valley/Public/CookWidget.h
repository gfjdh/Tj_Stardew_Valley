#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CookMenuRow.h"

#include "CookWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UCookWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCookMenuRow* CookMenuRowA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCookMenuRow* CookMenuRowB;

	bool IsOpen = false;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseButtonClicked();

	void DisplayWidget(bool bIsVisible);
};
