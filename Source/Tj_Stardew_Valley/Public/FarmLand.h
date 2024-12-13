// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/TimerHandle.h"

#include "FarmLand.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API AFarmLand : public AActor
{
	GENERATED_BODY()
	
public:	

	//初始化胶囊体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	//初始化耕地Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* FarmLandSprite;

	//标记当前挖的地块是否为耕地
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsFarmLand = false;

	// 构造函数初始化
	AFarmLand();

	// 游戏开始时调用
	virtual void BeginPlay() override;
	
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	//向当前地块耕地
	void HoeFarmLand();

	//给耕地浇水
	void WaterFarmLand();

	//耕地干燥时间
	void DryFarmLandTimeOut();
};
