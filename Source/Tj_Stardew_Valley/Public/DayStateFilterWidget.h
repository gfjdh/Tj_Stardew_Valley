#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CGameMode.h"

#include "DayStateFilterWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UDayStateFilterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	ACGameMode* GameMode;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* DayStateImage;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	float Transparency = 0.4f;
public:
	void SetFilterTransparency();
};
