#include "FishingWidget.h"

void UFishingWidget::EnableDisplay(bool IsEnable)
{
	//显示或隐藏UI
	if(IsEnable)
		AddToViewport();
	else
		RemoveFromParent();
}

void UFishingWidget::BeginFishing()
{
	//开始钓鱼
	IsInGame = true;
	EnableDisplay(true);
}

void UFishingWidget::EndFishing()
{
	//结束钓鱼
	IsInGame = false;
	//重置状态
	GamePercentage = 0.0f;
	FishPositionY = InitialFishPositionY;
	GreenZonePositionY = InitialGreenZonePositionY;
	EnableDisplay(false);
}

void UFishingWidget::UpdateProgressBar()
{
	//更新进度条
	FishingProgressBar->SetPercent(GamePercentage / 100.0f);
}

void UFishingWidget::SetPercentage(float Percentage)
{
	//设置进度条
	GamePercentage = Percentage;
	if (GamePercentage > 100.0f)
		GamePercentage = 100.0f;
	if (GamePercentage < 0.0f)
		GamePercentage = 0.0f;
}

void UFishingWidget::SetFishPosition(float PositionY)
{
	////设置鱼的位置
	//if (PositionY > MaxRangeY)
	//	PositionY = MaxRangeY;
	//if (PositionY < MinRangeY)
	//	PositionY = MinRangeY;
	////变速移动到制定为止：要求加速->(匀速)->减速
	//FishPositionY = FMath::FInterpTo(FishPositionY, PositionY, 0.1f, 0.5f);
	//FishImage->SetRenderTranslation(FVector2D(FishPositionX, FishPositionY));
}


void UFishingWidget::UpdateGreenZonePosition(float NewPositionY)
{
	//设置绿色区域的位置
	if (NewPositionY > MaxRangeY)
		NewPositionY = MaxRangeY;
	if (NewPositionY < MinRangeY)
		NewPositionY = MinRangeY;
	GreenZonePositionY = NewPositionY;
	GreenZone->SetRenderTranslation(FVector2D(0, GreenZonePositionY - InitialGreenZonePositionY));
}

