#include "FishingWidget.h"

void UFishingWidget::EnableDisplay(bool IsEnable)
{
	//��ʾ������UI
	if(IsEnable)
		AddToViewport();
	else 
		RemoveFromViewport();
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
	float PositionX = -30.0f;
	FishImage->SetRenderTranslation(FVector2D(PositionX, PositionY));
}
