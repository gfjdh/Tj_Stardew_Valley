// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookPot.h"
#include "WorkBench.generated.h"

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API AWorkBench : public ACookPot
{
	GENERATED_BODY()
	

	void OpenCookMenu(AActor* OtherActor) override;
};
