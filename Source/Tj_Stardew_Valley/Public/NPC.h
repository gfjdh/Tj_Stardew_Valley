#pragma once
#include "CoreMinimal.h"

#include "PaperZDCharacter.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

#include "NPC.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ANPC : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:	

	ANPC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent *NPC_CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent *NPCFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAlive = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool MoveStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementCoolDown = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementDuration = 1.0f;

	FTimerHandle MoveCoolDownTimer;
	FTimerHandle MoveDurationTimer;
	FTimerHandle SpawnProductTimer;

	void Move();
	void OnMoveCoolDownTimerTimeout();
	void OnMoveDurationTimerTimeout();
	void UpdateDirection();
};
