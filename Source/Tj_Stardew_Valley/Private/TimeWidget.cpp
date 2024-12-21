#include "TimeWidget.h"
#include "Slate.h"
#include "SlateCore.h"


void UTimeWidget::SetSeasonImage(UTexture2D* Texture)
{
	SeasonTextImage->SetBrushFromTexture(Texture);
}

void UTimeWidget::SetClockPointer(float DeltaDegree)
{
	ClockPointerImage->SetRenderTransformPivot(FVector2D(0.5, 1.0));
	//设置角度为Degree(与正上方的夹角)
	ClockPointerImage->SetRenderTransformAngle(DeltaDegree);
}
