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
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
	}
}

void UCookWidget::DisplayWidget(bool bIsVisible)
{
	if (bIsVisible) {
		AddToViewport();
		CookMenuRowB->ButtonCanClicked(1);
	}
	else {
		RemoveFromParent();
	}
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
	}
}


