#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "CollectableEntity.h"

#include "CookMenuRow.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API UCookMenuRow : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CookButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* MaterialA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* MaterialB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACollectableEntity> CollectableEntityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaterialIndexA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaterialIndexB;

public:
	UFUNCTION()
	void OnCookButtonClicked();

	virtual void NativeConstruct() override;
};