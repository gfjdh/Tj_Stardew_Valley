// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"




#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GoldText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;


	void SetStamina(int NewStamina);

	void SetGold(int Amount);

	void SetLevel(int FarmLevel,int ToolLevel,int CookLevel);
};
