#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Actor.h"
#include "CollectableEntity.h"
#include "SkillStates.h"

#include "Ores.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API AOres : public AActor
{
	GENERATED_BODY()

public:
	AOres();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* OreSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACollectableEntity> ProductClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDropNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinDropNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health = 1;

public:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Mine(AActor* OtherActor, USkillStates* PlayerSkill);
};
