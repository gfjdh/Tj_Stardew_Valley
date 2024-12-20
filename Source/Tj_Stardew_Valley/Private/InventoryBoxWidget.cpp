#include "InventoryBoxWidget.h"
#include "Inventory.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyPaperZDCharacter.h"

void UInventoryBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (BoxImage)
	{
		BoxImage->OnClicked.AddDynamic(this, &UInventoryBoxWidget::OnBoxImageClicked);
	}
}

void UInventoryBoxWidget::UpdateItemDisplay()
{
	//显示或隐藏ItemImage
	if (ItemVisible) {
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UInventoryBoxWidget::SetItemCounts(int32 Counts)
{
	if (!CurrentItem) {
		ItemCounts->SetText(FText::FromString(""));
		ItemVisible = false;
		return;
	}
	CurrentItem->CurrentAmount = Counts;
	if (Counts >= 2) {
		ItemCounts->SetText(FText::FromString(FString::FromInt(Counts)));
	}
	else {
		ItemCounts->SetText(FText::FromString(""));
	}

	if (Counts > 0)
	{
		ItemVisible = true;
	}
	else
	{
		ItemVisible = false;
	}
}

void UInventoryBoxWidget::SetItemImage(UTexture2D* Image)
{
	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(Image);
	}
}

void UInventoryBoxWidget::OnBoxImageClicked()
{
	if (UKismetSystemLibrary::GetGameTimeInSeconds(this) - LastClickTime < DoubleClickDeltaTime)
	{
		OnBoxImageDoubleClicked();
	}
	else
	{
		LastClickTime = UKismetSystemLibrary::GetGameTimeInSeconds(this);
	}
}

void UInventoryBoxWidget::OnBoxImageDoubleClicked()
{
	//将当前物品切换为当前格子的物品
	if (CurrentItem)
	{
		AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
		if (PlayerActor)
		{
			AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
			if (Player) {
				Player->PlayerInventory->UsingIndex = Index;
				Player->CurrentUsingItemWidget->FlushSlot(Player->PlayerInventory);
			}
		}
	}
}
