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
	//ԭ����--��ʳ��++
	//get inventory
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player) {
		UInventory* Inventory = Player->PlayerInventory;
		if (Inventory) {
			//�������Ƿ��㹻
			if (Inventory->HasItem(MaterialIndexA) && Inventory->HasItem(MaterialIndexB)) {
				Inventory->RemoveItem(MaterialIndexA, 1);
				Inventory->RemoveItem(MaterialIndexB, 1);
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

