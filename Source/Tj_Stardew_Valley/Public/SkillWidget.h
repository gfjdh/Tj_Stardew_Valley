// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "SkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API USkillWidget : public UUserWidget
{
public:
	GENERATED_BODY()
	
	//种植技能绑定
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HoeSkillLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HoeSkillLevel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CookSkillLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CookSkillLevel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CraftSkillLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CraftSkillLevel2;

	//按钮点击句柄
	UFUNCTION()
	void OnHoeSkillLevel1Clicked();

	UFUNCTION()
	void OnHoeSkillLevel2Clicked();

	UFUNCTION()
	void OnCookSkillLevel1Clicked();

	UFUNCTION()
	void OnCookSkillLevel2Clicked();

	UFUNCTION()
	void OnCraftSkillLevel1Clicked();

	UFUNCTION()
	void OnCraftSkillLevel2Clicked();

	UFUNCTION(BlueprintCallable)
	virtual void NativeConstruct() override;
};
