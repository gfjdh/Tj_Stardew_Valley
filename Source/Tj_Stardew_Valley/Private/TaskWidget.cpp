#include "TaskWidget.h"
#include "MyPaperZDCharacter.h"

void UTaskWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UTaskWidget::OnCloseButtonClicked);
	}
}

void UTaskWidget::OnCloseButtonClicked()
{
	if (IsOpened)
	{
		CloseTaskWidget();
	}
}

void UTaskWidget::ShowCurrentTasks(AActor* PlayerActor)
{
	if (PlayerActor) {
		AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
		if (Player) {
			//获取玩家当前任务
			TArray<FQuest> Quests = Player->Quests;
			int TaskCnt = 0;
			for (const auto& Quest : Quests)
			{
				if (!Quest.bIsCompleted) {
					TaskCnt++;
					UTaskItemWidget* TaskItemWidget = CreateWidget<UTaskItemWidget>(GetWorld(), TaskItemWidgetClass);
					if (TaskItemWidget)
					{
						// Description + RewardGold
						FString TaskInfo = Quest.Description + FString::Printf(TEXT("     RewardGold: %d"), Quest.RewardGold);
						TaskItemWidget->TaskInfo->SetText(FText::FromString(TaskInfo));
						TaskGridPanel->AddChild(TaskItemWidget);
					}
				}
			}
			if (Quests.Num() == 0 || TaskCnt == 0)
			{
				UTaskItemWidget* TaskItemWidget = CreateWidget<UTaskItemWidget>(GetWorld(), TaskItemWidgetClass);
				if (TaskItemWidget)
				{
					TaskItemWidget->TaskInfo->SetText(FText::FromString("No Tasks"));
					TaskGridPanel->AddChild(TaskItemWidget);
				}
			}
		}
	}
}

void UTaskWidget::CloseTaskWidget()
{
	IsOpened = false;
	//清空GridPanel的所有子控件
	if (TaskGridPanel)
		TaskGridPanel->ClearChildren();
	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
	if (PlayerActor) {
		AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
		Player->ActivatePlayer(true);
		Player->CurrentPlayerState = EPlayerState::Idle;
	}
	RemoveFromParent();
}