#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
}

void UMainMenuWidget::OnStartButtonClicked()
{
	//继续时间
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	RemoveFromParent();
}

void UMainMenuWidget::SetActive()
{
	//暂停时间
	GetWorld()->GetFirstPlayerController()->SetPause(true);
	AddToViewport();
}
