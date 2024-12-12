// Fill out your copyright notice in the Description page of Project Settings.


#include "StardrewGameInstance.h"

UStardrewGameInstance::UStardrewGameInstance() {
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("PlayerInventory"));
}
void UStardrewGameInstance::SetPlayerStamina(int NewStamina) {
	Stamina = NewStamina;
}

void UStardrewGameInstance::SetPlayerGold(int Coins) {
	GoldWealth += Coins;
}

void UStardrewGameInstance::SetPlayerLevel(int UpLevel) {
	Level += UpLevel;
}