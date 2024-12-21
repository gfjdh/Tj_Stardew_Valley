#include "CookMenuRow.h"

void UCookMenuRow::NativeConstruct()
{
	Super::NativeConstruct();
	CookButton->OnClicked.AddDynamic(this, &UCookMenuRow::OnCookButtonClicked);
}

void UCookMenuRow::OnCookButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cook Button Clicked"));
	//ԭ����--��ʳ��++
}

