// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MyPaperZDCharacter.h"
#include "TimerManager.h"

#include "TeleportPoint.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ATeleportPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportPoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TeleportArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Target")
	FVector Target;

	FTimerHandle DelayTimerHandle;

	bool WhetherToTeleport;

	UFUNCTION()
	void Teleport(AMyPaperZDCharacter* Player);

	void SetWhetherToTeleport(bool judge) { WhetherToTeleport = judge; }

	UFUNCTION()
	void TeleportAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
