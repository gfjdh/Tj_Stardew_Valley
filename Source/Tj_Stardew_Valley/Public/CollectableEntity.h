// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "Item.h"


#include "CollectableEntity.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ACollectableEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* ItemSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CollectableType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemId = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExpValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItem* ItemData;

	// Sets default values for this actor's properties
	ACollectableEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
