// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "NoticeSigns.generated.h"

/**
 * 
 */
UCLASS()
class TJ_STARDEW_VALLEY_API ANoticeSigns : public ANPC
{
	GENERATED_BODY()
	
public:
	ANoticeSigns();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	bool bIsVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	FString InvisiblePeriod; 
};