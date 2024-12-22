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
}


