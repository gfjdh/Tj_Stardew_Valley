#include "TaskWidget.h"
#include "MyPaperZDCharacter.h"

void UTaskWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UTaskWidget::OnCloseButtonClicked);
	}
}

void UTaskWidget::OnCloseButtonClicked()
{
	if (IsOpened)
	{
		IsOpened = false;
		RemoveFromParent();
		AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
		if (PlayerActor) {
			AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
			Player->ActivatePlayer(true);
			Player->CurrentPlayerState = EPlayerState::Idle;
		}
	}
}
