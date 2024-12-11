#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "FishingWidget.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UFishingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* FishingProgressBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* BlackCover;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* UI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* FishImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* GreenZone;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* FishHint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRangeY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinRangeY = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FishPosition = -40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenZonePoisition = -30.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsInGame = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GamePercentage = 0.0f;

public:
	void EnableDisplay(bool IsEnable);
	void BeginFishing();
	void EndFishing();
	void UpdateProgressBar();
	void SetFishPosition(float PositionY);
	void SetGreenZonePosition(float PositionY);
};
