// Fill out your copyright notice in the Description page of Project Settings.


#include "CSkillWidget.h"

//设置技能点数文本
void UCSkillWidget::SkillPointText(int FarmingPoint, int ToolPoint, int CookingPoint)
{
	FString PointString;
		PointString = FString::Printf(TEXT("FarmingSkillPoints:%d"),FarmingPoint);
		this->FarmingSkillPoint->SetText(FText::FromString(PointString));
		PointString = FString::Printf(TEXT("ToolSkillPoints:%d"), ToolPoint);
		this->ToolSkillPoint->SetText(FText::FromString(PointString));
		PointString = FString::Printf(TEXT("CookSkillPoints:%d"), CookingPoint);
		this->CookSkillPoint->SetText(FText::FromString(PointString));
}