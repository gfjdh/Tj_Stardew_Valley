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
	//����״̬
	GamePercentage = 0.0f;
	FishPositionY = InitialFishPositionY;
	GreenZonePositionY = InitialGreenZonePositionY;
	EnableDisplay(false);
}

void UFishingWidget::UpdateProgressBar()
{
	//���½�����
	FishingProgressBar->SetPercent(GamePercentage / 100.0f);
}

void UFishingWidget::SetPercentage(float Percentage)
{
	//���ý�����
	GamePercentage = Percentage;
	if (GamePercentage > 100.0f)
		GamePercentage = 100.0f;
	if (GamePercentage < 0.0f)
		GamePercentage = 0.0f;
}

void UFishingWidget::SetFishPosition(float PositionY)
{
	////�������λ��
	//if (PositionY > MaxRangeY)
	//	PositionY = MaxRangeY;
	//if (PositionY < MinRangeY)
	//	PositionY = MinRangeY;
	////�����ƶ����ƶ�Ϊֹ��Ҫ�����->(����)->����
	//FishPositionY = FMath::FInterpTo(FishPositionY, PositionY, 0.1f, 0.5f);
	//FishImage->SetRenderTranslation(FVector2D(FishPositionX, FishPositionY));
}


void UFishingWidget::UpdateGreenZonePosition(float NewPositionY)
{
	//������ɫ�����λ��
	if (NewPositionY > MaxRangeY)
		NewPositionY = MaxRangeY;
	if (NewPositionY < MinRangeY)
		NewPositionY = MinRangeY;
	GreenZonePositionY = NewPositionY;
	GreenZone->SetRenderTranslation(FVector2D(0, GreenZonePositionY - InitialGreenZonePositionY));
}

