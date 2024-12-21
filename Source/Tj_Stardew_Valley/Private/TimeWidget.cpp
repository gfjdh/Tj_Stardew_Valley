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

void UTimeWidget::SetTimeText(int Day, float CurrentTime)
{
	FString TimeString;
	if(CurrentTime <= 10.0)
		TimeString = FString::Printf(TEXT("Day %d 0%d:%d0"), Day, (int)CurrentTime, ((int)(CurrentTime * 10) - ((int)CurrentTime)*10) / 5 * 3);
	else
		TimeString = FString::Printf(TEXT("Day %d %d:%d0"), Day, (int)CurrentTime, ((int)(CurrentTime * 10) - ((int)CurrentTime) * 10) / 5 * 3);
	TimeText->SetText(FText::FromString(TimeString));
}
