// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"

#include "SkillsTypes.generated.h"


UENUM(BlueprintType)
enum class SkillType : uint8
{
	Endurance,
	Farming,
	Fishing,
	Chopping,
	Mining,
	Cooking,
	Interacting,
	Foraging,
	Crafting,
	Tool
};


USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Describe = TEXT("None");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SkillType SkillType = SkillType::Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* SkillSprite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillStage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStage = 3;


	FSkillData()
	{
		SkillID = -1;
		SkillName = TEXT("None");
		Describe = TEXT("None");
		SkillType = SkillType::Endurance;
		SkillSprite = nullptr;
		SkillStage = 1;
		MaxStage = 3;
	}

};

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API USkillsTypes : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExpToNextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillStructName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillStage;

	USkillsTypes()
	{
		Level = 1;
		Exp = 0;
		SkillPoint = 0;
		ExpToNextLevel = 50;
		SkillStructName = TEXT("None");
		SkillStage = 1;
	}
	

	UFUNCTION()
	void UpdateLevel(int32 ExValue);
};
