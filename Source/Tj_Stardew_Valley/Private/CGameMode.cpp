#include "CGameMode.h"

ACGameMode::ACGameMode()
{
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
	if (CurrentTicks >= 60 * 30) //30s = 游戏内一分钟
	{
		CurrentTicks = 0;
		CurrentTime += 1;
		if (CurrentTime >= 24) {
			CurrentTime = 0;
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
	}
}

void ACGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}
