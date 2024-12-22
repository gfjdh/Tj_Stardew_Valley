#include "CookMenuRow.h"
#include "MyPaperZDCharacter.h"

void UCookMenuRow::NativeConstruct()
{
	Super::NativeConstruct();
	CookButton->OnClicked.AddDynamic(this, &UCookMenuRow::OnCookButtonClicked);
}

void UCookMenuRow::OnCookButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cook Button Clicked"));
	//原材料--，食物++
	//get inventory
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) {
		//检查经验是否足够
		if (Player->PlayerSkill->Cooking->Exp < DesiredExp) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You don't have enough EXP!"));
			return;
		}
		UInventory* Inventory = Player->PlayerInventory;
		if (Inventory) {
			//检查材料是否足够
			if (Inventory->HasItem(MaterialIndexA) && Inventory->HasItem(MaterialIndexB)) {
				Inventory->RemoveItem(MaterialIndexA, 1);
				Inventory->RemoveItem(MaterialIndexB, 1);
				//加经验
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Add EXP 10!"));
				Player->PlayerSkill->SkillStrucUpdate(SkillType::Cooking, 10);
				//在玩家脚底生成食物
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

