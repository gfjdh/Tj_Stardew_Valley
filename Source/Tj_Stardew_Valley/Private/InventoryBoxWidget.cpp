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
#include "InventoryDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

void UInventoryBoxWidget::OnBoxDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (CurrentItem)
	{
		UInventoryDragDropOperation* DragDropOperation = NewObject<UInventoryDragDropOperation>();
		DragDropOperation->DraggedWidget = this;
		DragDropOperation->DraggedIndex = Index;

		UWidgetBlueprintLibrary::CreateDragDropOperation(UInventoryDragDropOperation::StaticClass());
		UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}
}

void UInventoryBoxWidget::OnBoxDropped(UDragDropOperation* Operation)
{
	UInventoryDragDropOperation* DragDropOperation = Cast<UInventoryDragDropOperation>(Operation);
	if (DragDropOperation && DragDropOperation->DraggedWidget)
	{
		SwapItem(DragDropOperation->DraggedIndex);
	}
}

void UInventoryBoxWidget::SwapItem(int DragIndex)
{
	if (CurrentItem)
	{
		AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPaperZDCharacter::StaticClass());
		if (PlayerActor)
		{
			AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(PlayerActor);
			if (Player) {
				UInventory* Inventory = Player->PlayerInventory;
				UItem* TempItem = Inventory->Inventory[DragIndex];
				Inventory->Inventory[DragIndex] = CurrentItem;
				CurrentItem = TempItem;
				UpdateItemDisplay();
			}
		}
	}
}