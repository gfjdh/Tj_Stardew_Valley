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

FReply UInventoryBoxWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NativeOnMouseButtonDown"));
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
}

void UInventoryBoxWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (CurrentItem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NativeOnDragDetected"));
		UInventoryDragDropOperation* DragDropOperation = NewObject<UInventoryDragDropOperation>();
		DragDropOperation->DraggedWidget = this;
		DragDropOperation->DraggedIndex = Index;
		DragDropOperation->Payload = this;
		DragDropOperation->Pivot = EDragPivot::MouseDown;
		//��ק��ʽ
		DragDropOperation->DefaultDragVisual = this;
		DragDropOperation->Offset = FVector2D(0.0f, 0.0f);
		OutOperation = DragDropOperation;
	}
}

bool UInventoryBoxWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NativeOnDrop"));
	UInventoryDragDropOperation* DragDropOperation = Cast<UInventoryDragDropOperation>(InOperation);
	if (DragDropOperation && DragDropOperation->DraggedWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Swap Item"));
		SwapItem(DragDropOperation->DraggedIndex);
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryBoxWidget::UpdateItemDisplay()
{
	//��ʾ������ItemImage
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
	//����ǰ��Ʒ�л�Ϊ��ǰ���ӵ���Ʒ
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