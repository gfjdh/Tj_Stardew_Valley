// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

#include "NPC.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLines
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> Lines;
};

UENUM(BlueprintType)
enum class ENPCGender : uint8
{
	Male UMETA(DisplayName = "Male"),
	Female UMETA(DisplayName = "Female")
};

UCLASS()
class TJ_STARDEW_VALLEY_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent *NPCCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent *NPCFlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWidgetComponent *DialogueWidgetComponent;
	
	// ��ӶԻ��ַ�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueLines> DialogueLines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = "true"))
	ENPCGender Gender;

	// ����NPC�ƶ���������ĺͰ뾶
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementAreaCenter;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementAreaRadius;

	// ����NPC�ƶ��ٶ�
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed;

	FVector CurrentDirection;
	float TimeToChangeDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleUpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleDownAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleLeftAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *IdleRightAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveUpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveDownAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveLeftAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook *MoveRightAnimation;

	ANPC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	FRandomStream RandomStream;// �����������
	bool bIsDialogueVisible;// �Ի��ɼ���״̬

	// �øж����
	int32 Favorability;
	int32 FavorabilityLevel;
	void IncreaseFavorability();
	void CheckFavorabilityLevel();

	// ����NPC����ƶ�
	void MoveRandomly(float DeltaTime);

	void UpdateAnimation();

	// ���ѡ��һ���Ի��ַ�������ʾ
	void DisplayRandomDialogue();

	// �������Ƿ񿿽��������Ի�
	void CheckForPlayerInteractionBox();
};
