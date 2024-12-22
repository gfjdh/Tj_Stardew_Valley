#include "NoticeSigns.h"
#include "CGameMode.h"

ANoticeSigns::ANoticeSigns()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsVisible = true;
	InvisiblePeriod = "";
}

void ANoticeSigns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode)
	{
		int32 CurrentDay = GameMode->GetCurrentDay();
		FString CurrentDate = FString::FromInt(CurrentDay);

		if (InvisiblePeriod == CurrentDate)
		{
			bIsVisible = false;
		}
		else
		{
			bIsVisible = true;
		}
	}

	if (!bIsVisible)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = -100.0f;
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = 10.0f;
		SetActorLocation(NewLocation);
	}
}
