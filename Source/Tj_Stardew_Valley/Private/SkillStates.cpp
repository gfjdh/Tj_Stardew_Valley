// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillStates.h"

// Sets default values for this component's properties
USkillStates::USkillStates()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//耐力部分技能初始化
	SkillInit(1, EnduranceSaver);
	SkillInit(2, EnduranceStander);
	SkillInit(3, EnduranceMaxMaster);


	Endurance = CreateDefaultSubobject<USkillsTypes>(TEXT("Endurance"));
	Endurance->SkillStructName = TEXT("Endurance");

	Farming = CreateDefaultSubobject<USkillsTypes>(TEXT("Farming"));
	Farming->SkillStructName = TEXT("Farming");

	Fishing = CreateDefaultSubobject<USkillsTypes>(TEXT("Fishing"));
	Fishing->SkillStructName = TEXT("Fishing");

	Chopping = CreateDefaultSubobject<USkillsTypes>(TEXT("Chopping"));
	Chopping->SkillStructName = TEXT("Chopping");

	Tool = CreateDefaultSubobject<USkillsTypes>(TEXT("Tool"));
	Tool->SkillStructName = TEXT("Tool");

	Mining = CreateDefaultSubobject<USkillsTypes>(TEXT("Mining"));
	Mining->SkillStructName = TEXT("Mining");

	Cooking = CreateDefaultSubobject<USkillsTypes>(TEXT("Cooking"));
	Cooking->SkillStructName = TEXT("Cooking");

	Interacting = CreateDefaultSubobject<USkillsTypes>(TEXT("Interacting"));
	Interacting->SkillStructName = TEXT("Interacting");

	Foraging = CreateDefaultSubobject<USkillsTypes>(TEXT("Foraging"));
	Foraging->SkillStructName = TEXT("Foraging");

	Crafting = CreateDefaultSubobject<USkillsTypes>(TEXT("Crafting"));
	Crafting->SkillStructName = TEXT("Crafting");

	//初始化技能结构
	
	// ...

	// ...
}


// Called when the game starts
void USkillStates::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillStates::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USkillStates::SkillInit(int32 SkillID, FSkillData& Skill)
{
	//int i = 0;
	static const FString ContextString(TEXT("Skill Data Context"));
	SkillDataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Skills/SkillTable.SkillTable'"));
	if (SkillDataTable)
	{
		FString LocalContextString;
		FName SkillRowName = FName(*FString::FromInt(SkillID));
		FSkillData* SkillData = SkillDataTable->FindRow<FSkillData>(SkillRowName, LocalContextString);
		if (SkillData)
		{
			Skill.SkillID = SkillData->SkillID;
			Skill.Describe = SkillData->Describe;
			Skill.SkillName = SkillData->SkillName;
			Skill.SkillType = SkillData->SkillType;
			Skill.SkillSprite = SkillData->SkillSprite;
			Skill.SkillStage = SkillData->SkillStage;
			Skill.MaxStage = SkillData->MaxStage;
			/*if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
				FString::Printf(TEXT("Skill ID %d found in DataTable"), SkillID));*/
		}
		else
		{
			/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				FString::Printf(TEXT("Skill ID %d not found in DataTable"), SkillID));*/
		}
	}
	else
	{
		/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			TEXT("Failed to load Skill DataTable"));*/
	}
}


bool USkillStates::SkillLevelUp(FSkillData& Skill) {
	if (Skill.SkillStage >= Skill.MaxStage) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("Skill %s reach max,return point"), *Skill.SkillName));
		return false;
	}
	else {
		Skill.SkillStage++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			FString::Printf(TEXT("Skill %s up to %d"), *Skill.SkillName, Skill.SkillStage));
	}
	return true;

}

void USkillStates::SkillStrucUpdate(SkillType SkillType, int32 ExpValue) {
	switch (SkillType)
	{
		case SkillType::Endurance:
			Endurance->UpdateLevel(ExpValue);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Stamina Exp gained!"));
			if (Endurance->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s point gained，open skill table and choose one skill to levelup"), *Endurance->SkillStructName));
				SkillPointUse(SkillType::Endurance, Index);
			}
			break;
		case SkillType::Fishing:
			Fishing->UpdateLevel(ExpValue);
			if (Fishing->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Fishing->SkillStructName));
			}
			break;
		case SkillType::Cooking:
			Cooking->UpdateLevel(ExpValue);
			if (Cooking->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Cooking->SkillStructName));
			}
			break;
		case SkillType::Interacting:
			Interacting->UpdateLevel(ExpValue);
			if (Interacting->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Interacting->SkillStructName));
			}
			break;
		case SkillType::Foraging:
			Foraging->UpdateLevel(ExpValue);
			if (Foraging->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Foraging->SkillStructName));
			}
			break;
		case SkillType::Farming:
			Farming->UpdateLevel(ExpValue);
			if (Farming->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Farming->SkillStructName));
			}
		case SkillType::Tool:
		case SkillType::Chopping:
		case SkillType::Mining:
			Tool->UpdateLevel(ExpValue);
			if (Tool->SkillPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
					FString::Printf(TEXT("SkillStruc %s ，open skill table and choose one skill to levelup"), *Tool->SkillStructName));
			}
			break;
		
	}
}

void USkillStates::SkillPointUse(SkillType SkillType, int32 SkillID) {
	switch (SkillType)
	{
		case SkillType::Endurance:
			if (Endurance->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(EnduranceSaver);
					Endurance->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(EnduranceStander);
					Endurance->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(EnduranceMaxMaster);
					Endurance->SkillPoint--;
				}
			}
			break;
		/*case SkillType::Farming:
			if (Farming->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(FarmingSaver);
					Farming->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(FarmingHarvester);
					Farming->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(FarmingMaster);
					Farming->SkillPoint--;
				}
			}
			break;
		case SkillType::Fishing:
			if (Fishing->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(FishingSaver);
					Fishing->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(FishingHarvester);
					Fishing->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(FishingMaster);
					Fishing->SkillPoint--;
				}
			}
			break;
		case SkillType::Chopping:
			if (Chopping->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(ChoppingExpert);
					Chopping->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(ChoppingHarvest);
					Chopping->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(ChoppingEndurancer);
					Chopping->SkillPoint--;
				}
			}
			break;
		case SkillType::Mining:
			if (Mining->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(MiningExpert);
					Mining->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(MiningHarvest);
					Mining->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(MiningEndurancer);
					Mining->SkillPoint--;
				}
			}
			break;
		case SkillType::Cooking:
			if (Cooking->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(CookingExpert);
					Cooking->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(CookingHarvest);
					Cooking->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(FastCooker);
					Cooking->SkillPoint--;
				}
			}
			break;
		case SkillType::Interacting:
			if (Interacting->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(InteractingExpert);
					Interacting->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(InteractingLover);
					Interacting->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(MasterBusinessman);
					Interacting->SkillPoint--;
				}
			}
			break;
		case SkillType::Foraging:
			if (Foraging->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(ForagingExpert);
					Foraging->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(ForagingHarvest);
					Foraging->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(ForagerEndurancer);
					Foraging->SkillPoint--;
				}
			}
			break;
		case SkillType::Crafting:
			if (Crafting->SkillPoint)
			{
				if (SkillID == 1)
				{
					SkillLevelUp(CraftingExpert);
					Crafting->SkillPoint--;
				}
				else if (SkillID == 2)
				{
					SkillLevelUp(CraftingHarvest);
					Crafting->SkillPoint--;
				}
				else if (SkillID == 3)
				{
					SkillLevelUp(ToolSeller);
					Crafting->SkillPoint--;
				}
			}
			break;*/
	}
}
void USkillStates::SwitchSkillIndex() {
	Index++;
	if (Index > 3) {
		Index = 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Stamina Exp gained!"));
	}
}
