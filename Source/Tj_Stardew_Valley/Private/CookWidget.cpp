#include "CookWidget.h"

void UCookWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddDynamic(this, &UCookWidget::OnCloseButtonClicked);
}

void UCookWidget::OnCloseButtonClicked()
{
	SetVisibility(false);
}

void UCookWidget::SetVisibility(bool bIsVisible)
{
	if (bIsVisible) {
		AddToViewport();
	}
	else {
		RemoveFromParent();
	}
}

