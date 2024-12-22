#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
}

void UMainMenuWidget::OnStartButtonClicked()
{
	//����ʱ��
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	RemoveFromParent();
}

void UMainMenuWidget::SetActive()
{
	//��ͣʱ��
	GetWorld()->GetFirstPlayerController()->SetPause(true);
	AddToViewport();
}
