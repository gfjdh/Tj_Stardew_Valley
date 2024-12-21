#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyPaperZDCharacter.h"

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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentTime = 0.0f;	//hours

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentDay = 1;		//days

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESeason CurrentSeason = ESeason::Spring;	//seasons

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDayState CurrentDayState = EDayState::Day;	//day state

	int CurrentTicks;	//ticks
};
