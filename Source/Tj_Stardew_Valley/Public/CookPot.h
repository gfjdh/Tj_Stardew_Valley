#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "CookPot.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API ACookPot : public AActor
{
	GENERATED_BODY()
	
public:	
	ACookPot();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PotSprite;



public:
	void OpenCookMenu(AActor* OtherActor);
};
