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
#include "CollectableEntity.h"

#include "Crop.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ACrop : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* TreeSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* DefectedSprite;

	//决定作物的当前成长状态，并以此来切换外观，和决定收获物
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int status=0;

	//作物的当前成熟度，以此决定作物当前的成长状态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	double Maturity=0;

	//作物各阶段对应的sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* CropStageSprite1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* CropStageSprite2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* CropStageSprite3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* CropStageSprite4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Buff_Empty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Buff_Defected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Buff_NeedWater;

	//作物被收获后生成的两个产物，分别是种子和产品
	UPROPERTY(EditDefaultsOnly, Category = "Product")
	TSubclassOf<ACollectableEntity> ProductActor1;

	UPROPERTY(EditDefaultsOnly, Category = "Product")
	TSubclassOf<ACollectableEntity> ProductActor2;

	//湿耕地才会生长
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsWet = 0;

	//病害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsDefected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DefectRate = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsDry = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DryRate = 60;


	// Sets default values for this actor's properties
	ACrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//改变当前作物状态的函数
	UFUNCTION()
	void JudgeMaturity();

	//改变当前作物外观
	UFUNCTION()
	void SwitchSprite();

	//生成产品
	UFUNCTION()
	void SpawnProducts();

	UFUNCTION()
	void GetDefect();


	UFUNCTION()
	void GetDry();

	UFUNCTION()
	void HealDef();

	UFUNCTION()
	void HealDry();
};
