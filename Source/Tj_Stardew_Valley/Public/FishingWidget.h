#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Engine/TimerHandle.h"

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
	float MaxRangeY = 740.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinRangeY = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FishPositionX = -40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FishPositionY = 570.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialFishPositionY = 570.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FishHeight = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenZonePoisitionX = -65.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenZonePositionY = 740.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitialGreenZonePositionY = 740.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenZoneHeight = 140.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsInGame = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GamePercentage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PercentageBarSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GreenZoneSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FishMovingCoolDown = 4.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanFishMove = true;

	float FishTargetPositionY = 0.0f;

	FTimerHandle FishMovingCoolDownTimer;
public:
	void EnableDisplay(bool IsEnable);
	void BeginFishing();
	void EndFishing();
	void UpdateProgressBar();
	void SetPercentage(float Percentage);
	void SetFishPosition(float NewPositionY);
	void UpdateGreenZonePosition(float NewPositionY);
	void SetFishRandomPosition();
	void OnFishMovingCoolDownTimerTimeout();
};
