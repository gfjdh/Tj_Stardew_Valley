#include "BackPackWidget.h"
#include "MyPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBackPackWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UBackPackWidget::OnExitButtonClicked);
	InitFlushBackPack();
}

void UBackPackWidget::InitFlushBackPack()
{
	if (BackPackGridSlot)
	{
		BackPackGridSlot->ClearChildren();
		for (int i = 0; i < BackPackSize; i++)
		{
			UInventoryBoxWidget* InventoryBox = CreateWidget<UInventoryBoxWidget>(this, InventoryBoxClass);
			BackPackGridSlot->AddChildToGrid(InventoryBox, i / BackPackSizePerRow, i % BackPackSizePerRow);
		}
	}
}

void UBackPackWidget::EnableDisplay(bool IsVisible)
{
	if (IsVisible)
		AddToViewport();
	else
		RemoveFromParent();
}

void UBackPackWidget::OnExitButtonClicked()
{
	IsOpen = false;
	EnableDisplay(false);

	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
	if (PlayerActor) {
		AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
		Player->ActivatePlayer(true);
		Player->CurrentPlayerState = EPlayerState::Idle;
	}
}