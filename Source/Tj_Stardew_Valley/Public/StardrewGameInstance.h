#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"


#include "StardrewGameInstance.generated.h"
UCLASS()
class TJ_STARDEW_VALLEY_API UStardrewGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite)
	int Stamina = 100;

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite)
	int GoldWealth = 0;

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite)
	int Level = 1;


	
	void SetPlayerStamina(int NewStamina);
	void SetPlayerGold(int Coins);
	void SetPlayerLevel(int UpLevel);
};
