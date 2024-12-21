#include "CookWidget.h"

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
	}
	else {
		RemoveFromParent();
	}
}

void UCookWidget::EnableCookMenuRow(int Index, bool bIsEnable)
{
	if (Index < CookMenuRow.Num()) {
		CookMenuRow[Index]->SetVisibility(bIsEnable ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

