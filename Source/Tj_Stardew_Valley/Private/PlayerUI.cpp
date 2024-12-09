// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"


void UPlayerUI::SetStamina(int NewStamina) {

	FString Str = FString::Printf(TEXT("Stamina: %d"), NewStamina);
	StaminaText->SetText(FText::FromString(Str));
}

void UPlayerUI::SetGold(int Amount) {

	FString Str = FString::Printf(TEXT("Gold: %d"), Amount);
	GoldText->SetText(FText::FromString(Str));
}

void UPlayerUI::SetLevel(int Index) {
	FString Str = FString::Printf(TEXT("Level: %d"), Index);
	LevelText->SetText(FText::FromString(Str));
}
