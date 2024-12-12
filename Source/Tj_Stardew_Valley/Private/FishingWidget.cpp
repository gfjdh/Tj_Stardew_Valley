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
	//重置状态
	GamePercentage = 0.0f;
	FishPositionY = InitialFishPositionY;
	GreenZonePositionY = InitialGreenZonePositionY;
	CanFishMove = true;
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

void UFishingWidget::SetFishPosition(float NewPositionY)
{
	//设置鱼的位置
	if (NewPositionY > MaxRangeY)
		NewPositionY = MaxRangeY;
	if (NewPositionY < MinRangeY)
		NewPositionY = MinRangeY;
	if (NewPositionY == FishPositionY) return;
	//变速移动到制定为止：要求加速->(匀速)->减速
	FishPositionY = FMath::FInterpTo(FishPositionY, NewPositionY, 0.1f, 0.5f);
	FishImage->SetRenderTranslation(FVector2D(0, FishPositionY - InitialFishPositionY));
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

void UFishingWidget::SetFishRandomPosition()
{
	if (CanFishMove) {
		//随机鱼的位置
		FishTargetPositionY = FMath::RandRange(MinRangeY, MaxRangeY);
		CanFishMove = false;
		GetWorld()->GetTimerManager().SetTimer(FishMovingCoolDownTimer, this, &UFishingWidget::OnFishMovingCoolDownTimerTimeout, 1.0f, false, FishMovingCoolDown);
	}
	SetFishPosition(FishTargetPositionY);
}

void UFishingWidget::OnFishMovingCoolDownTimerTimeout()
{
	//鱼移动冷却时间到
	CanFishMove = true;
}

