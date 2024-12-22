#include "CookWidget.h"
#include "MyPaperZDCharacter.h"

void UCookWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddDynamic(this, &UCookWidget::OnCloseButtonClicked);
}

void UCookWidget::OnCloseButtonClicked()
{
	DisplayWidget(false);
	//»ñµÃplayer
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) {
		Player->CurrentPlayerState = EPlayerState::Idle;
		Player->ActivatePlayer(true);
		IsOpen = false;
	}
}

void UCookWidget::DisplayWidget(bool bIsVisible)
{
	if (bIsVisible) {
		AddToViewport();
		IsOpen = true;
		CookMenuRowB->ButtonCanClicked(2);
	}
	else {
		RemoveFromParent();
	}
}


