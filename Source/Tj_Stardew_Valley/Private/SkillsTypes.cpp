// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillsTypes.h"



void  USkillsTypes::UpdateLevel(int32 ExValue) {
	Exp += ExValue;
	if (Exp >= ExpToNextLevel) {
		Exp = 0;
		Level++;
		if (Level % 5 == 0) {
			SkillPoint++;
		}
		ExpToNextLevel *= 1.2;
		if (GEngine) {
			FString LevelInfo = FString::Printf(TEXT("%s level up to %d"),*SkillStructName, Level);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, LevelInfo);
		}
	}
}