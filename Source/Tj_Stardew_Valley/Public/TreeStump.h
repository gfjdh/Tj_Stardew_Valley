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

#include "TreeStump.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ATreeStump : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* TreeSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACollectableEntity> ProductClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDropNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinDropNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health = 1;


	ATreeStump();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Chop(AActor* OtherActor);
};
