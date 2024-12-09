// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StardrewGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API UStardrewGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite)
	int Stamina = 100;

	void SetPlayerStamina(int NewStamina);
};
