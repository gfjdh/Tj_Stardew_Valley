#include "FishingWidget.h"

void UFishingWidget::EnableDisplay(bool IsEnable)
{
	//��ʾ������UI
	if(IsEnable)
		AddToViewport();
	else
		RemoveFromParent();
}

void UFishingWidget::BeginFishing()
{
	//��ʼ����
	IsInGame = true;
	EnableDisplay(true);
}

void UFishingWidget::EndFishing()
{
	//��������
	IsInGame = false;
	EnableDisplay(false);
}

void UFishingWidget::UpdateProgressBar()
{
	//���½�����
	FishingProgressBar->SetPercent(GamePercentage / 100.0f);
}

void UFishingWidget::SetFishPosition(float PositionY)
{
	//�������λ��
	if (PositionY > MaxRangeY)
		PositionY = MaxRangeY;
	if (PositionY < MinRangeY)
		PositionY = MinRangeY;
	FishImage->SetRenderTranslation(FVector2D(FishPosition, PositionY));
}

void UFishingWidget::SetGreenZonePosition(float PositionY)
{
	//������ɫ�����λ��
	if (PositionY > MaxRangeY)
		PositionY = MaxRangeY;
	if (PositionY < MinRangeY)
		PositionY = MinRangeY;
	GreenZone->SetRenderTranslation(FVector2D(GreenZonePoisition, PositionY));
}
