// TimeWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "TimeWidget.generated.h"

USTRUCT(BlueprintType)
struct FHoliday
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HolidayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HolidayDate;
};

UCLASS()
class TJ_STARDEW_VALLEY_API UTimeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage *ClockImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage *ClockPointerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage *SeasonTextImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock *TimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock *HolidayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHoliday> Holidays;

public:
	void SetSeasonImage(UTexture2D *Texture);
	void SetClockPointer(float DeltaDegree);
	void SetTimeText(int Day, float CurrentTime);
	void SetHolidayText(int Day);
};