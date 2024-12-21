#include "CGameMode.h"
#include "MyPaperZDCharacter.h"

ACGameMode::ACGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// 设置默认的Pawn类为自定义的MyPaperZDCharacter
	DefaultPawnClass = AMyPaperZDCharacter::StaticClass();
}

void ACGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTicks++;
	if (CurrentTicks >= 30 * 30 / TimeFlowSpeedRate) //900s = 游戏内0.5h
	{
		CurrentTicks = 0;
		CurrentTime += 0.5;
		if (CurrentTime >= 0 && CurrentTime < 12)
		{
			CurrentDayState = EDayState::Day;
		}
		else if (CurrentTime >= 12 && CurrentTime < 18)
		{
			CurrentDayState = EDayState::Afternoon;
		}
		else
		{
			CurrentDayState = EDayState::Night;
		}
		if (CurrentTime >= 24) {
			CurrentTime = 0;
			CurrentDay++;
			if (CurrentDay >= 30) {
				CurrentDay = 1;
				switch (CurrentSeason)
				{
					case ESeason::Spring:
						CurrentSeason = ESeason::Summer;
						break;
					case ESeason::Summer:
						CurrentSeason = ESeason::Fall;
						break;
					case ESeason::Fall:
						CurrentSeason = ESeason::Winter;
						break;
					case ESeason::Winter:
						CurrentSeason = ESeason::Spring;
						break;
					default:
						break;
				}
			}
		}
	}
}

void ACGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

void ACGameMode::SkipToday()
{
	CurrentTime = 24;
	CurrentTicks = 0;
	CurrentDay++;
	if (CurrentDay >= 30) {
		CurrentDay = 0;
		switch (CurrentSeason)
		{
			case ESeason::Spring:
				CurrentSeason = ESeason::Summer;
				break;
			case ESeason::Summer:
				CurrentSeason = ESeason::Fall;
				break;
			case ESeason::Fall:
				CurrentSeason = ESeason::Winter;
				break;
			case ESeason::Winter:
				CurrentSeason = ESeason::Spring;
				break;
			default:
				break;
		}
	}
}

int32 ACGameMode::GetCurrentDay() const
{
	return CurrentDay;
}