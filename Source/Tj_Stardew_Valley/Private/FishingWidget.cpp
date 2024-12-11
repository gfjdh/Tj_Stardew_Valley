#include "FishingWidget.h"

void UFishingWidget::EnableDisplay(bool IsEnable)
{
	//显示或隐藏UI
	if(IsEnable)
		AddToViewport();
	else 
		RemoveFromViewport();
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
	EnableDisplay(false);
}

void UFishingWidget::UpdateProgressBar()
{
	//更新进度条
	FishingProgressBar->SetPercent(GamePercentage / 100.0f);
}

void UFishingWidget::SetFishPosition(float PositionY)
{
	//设置鱼的位置
	float PositionX = -30.0f;
	FishImage->SetRenderTranslation(FVector2D(PositionX, PositionY));
}
