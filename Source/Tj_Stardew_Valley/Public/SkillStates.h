 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillsTypes.h"

#include "SkillStates.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TJ_STARDEW_VALLEY_API USkillStates : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USkillStates();

	//耐力技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData EnduranceSaver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData EnduranceStander;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData EnduranceMaxMaster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Endurance;


	//农业技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FarmingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FarmingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FarmingEndurancer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Farming;


	//钓鱼技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FishingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FishingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FishingEndurancer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Fishing;

	//砍树技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ChoppingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ChoppingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ChoppingEndurancer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Chopping;

	//工具技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ToolExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ToolHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ToolSaver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Tool;

	//挖矿技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData MiningExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData MiningHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData MiningEndurancer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Mining;

	//烹饪技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData CookingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData CookingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData FastCooker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Cooking;

	//互动技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData InteractingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData InteractingLover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData MasterBusinessman;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Interacting;

	//饲养技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ForagingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ForagingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ForagerEndurancer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Foraging;

	//制作技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData CraftingExpert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData CraftingHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillData ToolSeller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkillsTypes* Crafting;

	//技能表
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SkillDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SkillInit(int32 SkillID, FSkillData& Skill);

	UFUNCTION()
	bool SkillLevelUp(FSkillData& Skill);

	UFUNCTION()
	void SkillStrucUpdate(SkillType SkillType, int32 ExpValue);

	UFUNCTION()
	void SwitchSkillIndex();

	UFUNCTION()
	void SkillPointUse(SkillType SkillType, int32 SkillID);

};

