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
			//��ȡ��ҵ�ǰ����
			TArray<FQuest> Quests = Player->Quests;
			//��ӡ��������
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Quests Num: %d"), Quests.Num()));
			for (const auto& Quest : Quests)
			{
				if (!Quest.bIsCompleted) {
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
		}
	}
}

void UTaskWidget::CloseTaskWidget()
{
	IsOpened = false;
	//���GridPanel�������ӿؼ�
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