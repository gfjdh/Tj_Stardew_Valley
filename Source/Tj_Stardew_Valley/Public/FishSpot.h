#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "FishSpot.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API AFishSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	AFishSpot();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComp;

};
