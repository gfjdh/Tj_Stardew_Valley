#include "DayStateFilterWidget.h"

void UDayStateFilterWidget::SetFilterTransparency()
{
	if (GameMode == nullptr)
	{
		return;
	}
	//CurrentTime = 12ʱΪ0,24ʱΪ0.6
	Transparency = fabs(GameMode->CurrentTime - 12) / 24 * 0.8;
	DayStateImage->SetRenderOpacity(Transparency);
}
