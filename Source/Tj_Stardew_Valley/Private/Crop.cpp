// Fill out your copyright notice in the Description page of Project Settings.


#include "Crop.h"
#include "MyPaperZDCharacter.h"
#include <random>
#include <time.h>

// Sets default values
ACrop::ACrop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	TreeSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	TreeSprite->SetupAttachment(RootComponent);

	DefectedSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DefectedSprite"));
	DefectedSprite -> SetupAttachment(RootComponent);
	DefectedSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	DefectedSprite->SetRelativeLocation(FVector(0.0f, -20.0f, 0.0f)); // 设置初始位置
}

// Called when the game starts or when spawned
void ACrop::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACrop::OverlapBegin);
}

// Called every frame
void ACrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JudgeMaturity();
	SwitchSprite();
}

void ACrop::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AFarmLand* FarmLand = Cast<AFarmLand>(OtherActor);
	ACrop* Crop = Cast<ACrop>(OtherActor);
	if (FarmLand) {
		if (FarmLand->WaterStage == 0) {
			IsWet = 0;
		}
		else {
			IsWet = 1;
		}
	}
}


//改变当前作物状态的函数
void ACrop::JudgeMaturity()
{
	int temp_stat = status;
	srand(time(0));
	if (Maturity < 1000) {
		//作物的生长速度在一定范围内随机,受技能和季节影响
		if (!IsDefected && !IsDry) {
			Maturity += (double)(rand() % 5 / 10 + 0.5) * IsWet*GrowSpeed*SeasonSpeed[(int)Cast<ACGameMode>(GetWorld()->GetAuthGameMode())->CurrentSeason];
		}
	}
	if (Maturity < 200) {
		status = 0;
	}
	else if (Maturity >= 200 && Maturity < 500) {
		status = 1;
	}
	else if (Maturity >= 500 && Maturity < 1000) {
		status = 2;
	}
	else {
		status = 3;
	}
	if (temp_stat < status && status != 3) {
		GetDefect();
		GetDry();
	}
}

//改变当前作物外观
void ACrop::SwitchSprite()
{
	switch (status) {
	case 0:
		this->TreeSprite->SetSprite(CropStageSprite1);
		break;
	case 1:
		this->TreeSprite->SetSprite(CropStageSprite2);
		break;
	case 2:
		this->TreeSprite->SetSprite(CropStageSprite3);
		break;
	case 3:
		this->TreeSprite->SetSprite(CropStageSprite4);
		break;
	}
}

//生成产品
void ACrop::SpawnProducts()
{
	FVector CropLocation = this->GetActorLocation();
	srand(time(0));
	int OffsetX = (rand() - RAND_MAX) % 20;
	int OffsetY = (rand() - RAND_MAX) % 19;
	FVector ProductsSpawnLocation = CropLocation + FVector(OffsetX, OffsetY, 0);
	//成熟阶段收获，可以生成产品
	if (status == 3){
		for (int i = 0; i < HarvestTimes; i++) {
			GetWorld()->SpawnActor<ACollectableEntity>(ProductActor1, ProductsSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
		}
	}

	//生成种子,根据status成熟情况生成种子数
	for (int i = 1; i < status+2; i++) {
		srand(time(0) + i * 100);
		OffsetX = (rand() - RAND_MAX) % 20;
		OffsetY = (rand() - RAND_MAX) % 19;
		ProductsSpawnLocation = CropLocation + FVector(OffsetX, OffsetY, 0);
		GetWorld()->SpawnActor<ACollectableEntity>(ProductActor2, ProductsSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
	}

}

void ACrop::Fert() {
	Maturity += 500;
}

void ACrop::GetDefect() {
	if (!IsDefected && !IsDry) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Crop has not been defected!"));
		int RandomValue = FMath::RandRange(0, 100);
		if (RandomValue <= DefectRate)
		{
			IsDefected = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crop has been defected!"));
			DefectedSprite->SetSprite(Buff_Defected);

		}
	}
}


void ACrop::GetDry() {
	if (!IsDry && !IsDefected) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Crop has not been dryed!"));
		int RandomValue = FMath::RandRange(0, 100);
		if (RandomValue <= DryRate)
		{
			IsDry = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crop has been dryed!"));
			DefectedSprite->SetSprite(Buff_NeedWater);

		}
	}
}

void ACrop::HealDef() {
	IsDefected = false;
	DefectedSprite->SetSprite(Buff_Empty);
}


void ACrop::HealDry() {
	IsDry = false;
	DefectedSprite->SetSprite(Buff_Empty);
}

void ACrop::Expert(USkillStates* PlayerSkill)
{
	this->DefectRate /= PlayerSkill->FarmingExpert.SkillStage;
	this->DryRate /= PlayerSkill->FarmingExpert.SkillStage;
	this->GrowSpeed *= PlayerSkill->FarmingExpert.SkillStage;
}

void ACrop::Harvester(USkillStates* PlayerSkill)
{
	this->HarvestTimes *= PlayerSkill->FarmingHarvest.SkillStage;
}