#include "CookMenuRow.h"
#include "MyPaperZDCharacter.h"
#include "SkillStates.h"

void UCookMenuRow::NativeConstruct()
{
	Super::NativeConstruct();
	CookButton->OnClicked.AddDynamic(this, &UCookMenuRow::OnCookButtonClicked);
}

void UCookMenuRow::OnCookButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cook Button Clicked"));
	//ԭ����--��ʳ��++
	//get inventory
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) {
		//��龭���Ƿ��㹻
		if (Player->PlayerSkill->Cooking->Exp < DesiredExp) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You don't have enough EXP!"));
			return;
		}
		UInventory* Inventory = Player->PlayerInventory;
		if (Inventory) {
			//�������Ƿ��㹻
			if (Inventory->HasItem(MaterialIndexA) && Inventory->HasItem(MaterialIndexB)) {
				Inventory->RemoveItem(MaterialIndexA, 1);
				Inventory->RemoveItem(MaterialIndexB, 1);
				//�Ӿ���
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Add EXP 10!"));
				Player->PlayerSkill->SkillStrucUpdate(UpdateType, 100);
				Player->PlayerSkill->SkillStrucUpdate(UpdateType, 100);
				Player->PlayerSkill->SkillStrucUpdate(UpdateType, 100);
				Player->PlayerSkill->SkillStrucUpdate(UpdateType, 100);
				Player->PlayerSkill->SkillStrucUpdate(UpdateType, 100);
				//����ҽŵ�����ʳ��
				FVector SpawnLocation = Player->GetActorLocation();
				GetWorld()->SpawnActor<ACollectableEntity>(CollectableEntityClass, SpawnLocation, FRotator::ZeroRotator);
				//flush inventory
				Player->CurrentUsingItemWidget->FlushSlot(Inventory);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You don't have enough material!"));
			}
		}
	}
}

void UCookMenuRow::ButtonCanClicked(int LevelNeed)
{
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	switch (UpdateType)
	{
	case SkillType::Cooking:
		if (Player->PlayerSkill->Cooking->SkillStage <= LevelNeed) {
			//�ȼ��������úϳ�
			CookButton->OnClicked.RemoveAll(this);
			CookButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f));
		}
		else {
			CookButton->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	case SkillType::Tool:
		break;
	default:
		break;
	}
}

