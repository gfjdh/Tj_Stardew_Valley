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

	//��ʼ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	//��ʼ������Sprite���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* FarmLandSpriteComp;

	//��ʾ�ĸ���Sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* FarmLandSprite;

	//��ʼ��ʪ����Sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* WetFarmLandSprite;

	//��¼��ǰ���صĽ�ˮ�ȼ�����Ϊ�ɡ�ʪ��ÿ֡�½�1
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int WaterLevel = 0;

	//��¼��ǰ���صĽ�ˮ״̬����Ϊ�ɡ�ʪ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaterStage = 0;

	// ���캯����ʼ��
	AFarmLand();

	// ��Ϸ��ʼʱ����
	virtual void BeginPlay() override;
	
	// ÿ֡����
	virtual void Tick(float DeltaTime) override;

	//�����ؽ�ˮ
	void WaterFarmLand();

};
