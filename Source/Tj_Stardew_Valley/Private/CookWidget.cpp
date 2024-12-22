#include "CookWidget.h"
#include "MyPaperZDCharacter.h"

void UCookWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddDynamic(this, &UCookWidget::OnCloseButtonClicked);
	CookMenuRowA->SetVisibility(ESlateVisibility::Visible);
	CookMenuRowB->SetVisibility(ESlateVisibility::Visible);
}

void UCookWidget::OnCloseButtonClicked()
{
	DisplayWidget(false);
}

void UCookWidget::DisplayWidget(bool bIsVisible)
{
	if (bIsVisible) {
		AddToViewport();
	}
	else {
		RemoveFromParent();
	}
}


