#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeWidget.h"

#include "CGameMode.generated.h"

UENUM(BlueprintType)
enum class ESeason : uint8 {
	Spring,
	Summer,
	Fall,
	Winter
};

UENUM(BlueprintType)
enum class EDayState : uint8 {
	Day,
	Afternoon,
	Night
};

UCLASS()
class TJ_STARDEW_VALLEY_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float CurrentTime = 0.0f;	//hours

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CurrentDay = 1;		//days

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESeason CurrentSeason = ESeason::Spring;	//seasons

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDayState CurrentDayState = EDayState::Day;	//day state

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeFlowSpeedRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SpringTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SummerTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AutumnTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* WinterTexture;

	int CurrentTicks;	//ticks
public:
	void SkipToday();
};
