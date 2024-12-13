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

	//��ʼ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	//��ʼ������Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* FarmLandSprite;

	//��ǵ�ǰ�ڵĵؿ��Ƿ�Ϊ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsFarmLand = false;

	// ���캯����ʼ��
	AFarmLand();

	// ��Ϸ��ʼʱ����
	virtual void BeginPlay() override;
	
	// ÿ֡����
	virtual void Tick(float DeltaTime) override;

	//��ǰ�ؿ����
	void HoeFarmLand();

	//�����ؽ�ˮ
	void WaterFarmLand();

	//���ظ���ʱ��
	void DryFarmLandTimeOut();
};
