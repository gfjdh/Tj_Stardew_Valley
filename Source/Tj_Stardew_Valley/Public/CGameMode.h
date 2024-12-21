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
	float CurrentTime;	//hours

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentDay;		//days

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESeason CurrentSeason;	//seasons

	int CurrentTicks;	//ticks
};
