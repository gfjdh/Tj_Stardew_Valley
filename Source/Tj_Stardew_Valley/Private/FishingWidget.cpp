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
	//����״̬
	GamePercentage = 0.0f;
	FishPositionY = InitialFishPositionY;
	GreenZonePositionY = InitialGreenZonePositionY;
	CanFishMove = true;
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

void UFishingWidget::SetFishPosition(float NewPositionY)
{
	//�������λ��
	if (NewPositionY > MaxRangeY)
		NewPositionY = MaxRangeY;
	if (NewPositionY < MinRangeY)
		NewPositionY = MinRangeY;
	if (NewPositionY == FishPositionY) return;
	//�����ƶ����ƶ�Ϊֹ��Ҫ�����->(����)->����
	FishPositionY = FMath::FInterpTo(FishPositionY, NewPositionY, 0.1f, 0.5f);
	FishImage->SetRenderTranslation(FVector2D(0, FishPositionY - InitialFishPositionY));
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

void UFishingWidget::SetFishRandomPosition()
{
	if (CanFishMove) {
		//������λ��
		FishTargetPositionY = FMath::RandRange(MinRangeY, MaxRangeY);
		CanFishMove = false;
		GetWorld()->GetTimerManager().SetTimer(FishMovingCoolDownTimer, this, &UFishingWidget::OnFishMovingCoolDownTimerTimeout, 1.0f, false, FishMovingCoolDown);
	}
	SetFishPosition(FishTargetPositionY);
}

void UFishingWidget::OnFishMovingCoolDownTimerTimeout()
{
	//���ƶ���ȴʱ�䵽
	CanFishMove = true;
}

