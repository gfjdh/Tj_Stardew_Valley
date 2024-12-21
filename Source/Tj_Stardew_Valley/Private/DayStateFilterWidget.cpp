#include "DayStateFilterWidget.h"

void UDayStateFilterWidget::SetFilterTransparency()
{
	if (GameMode == nullptr)
	{
		return;
	}
	Transparency = GameMode->CurrentTime / 24.0f / 2.0f;
	DayStateImage->SetOpacity(Transparency);
}
