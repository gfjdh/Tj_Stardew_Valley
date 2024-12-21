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
	//���ýǶ�ΪDegree(�����Ϸ��ļн�)
	ClockPointerImage->SetRenderTransformAngle(DeltaDegree);
}
