// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

#include "NPC.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent *NPCCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent *NPCFlipbookComponent;



	ANPC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// 用于NPC随机移动
	void MoveRandomly(float DeltaTime);

	void UpdateAnimation();

	// 定义NPC移动区域的中心和半径
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementAreaCenter;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementAreaRadius;

	// 控制NPC移动速度
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;

	FVector CurrentDirection;
	float TimeToChangeDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleUpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleDownAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleLeftAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleRightAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveUpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveDownAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveLeftAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveRightAnimation;
};
