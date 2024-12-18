// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PaperFlipbookComponent.h"


#include "FarmLand.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API AFarmLand : public AActor
{
	GENERATED_BODY()
	
public:	

	//初始化胶囊体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	//初始化耕地Sprite组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* FarmLandSpriteComp;

	//显示的耕地Sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* FarmLandSprite;

	//初始化湿耕地Sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* WetFarmLandSprite;

	//记录当前耕地的浇水等级，分为干、湿，每帧下降1
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int WaterLevel = 0;

	//记录当前耕地的浇水状态，分为干、湿
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaterStage = 0;

	// 构造函数初始化
	AFarmLand();

	// 游戏开始时调用
	virtual void BeginPlay() override;
	
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	//给耕地浇水
	void WaterFarmLand();

};
