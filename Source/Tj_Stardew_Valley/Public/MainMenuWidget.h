#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "MainMenuWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartButton;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartButtonClicked();

	void SetActive();
};
