#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "MyPaperZDCharacter.h"
#include "Item.h"
#include "CollectableEntity.h"
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
	
	// 添加对话字符串数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueLines> DialogueLines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = "true"))
	ENPCGender Gender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = "true"))
	bool EnableFavorability;

	// 定义NPC移动区域的中心和半径
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementAreaCenter;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementAreaRadius;

	// 控制NPC移动速度
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

	// 任务数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuest> AvailableQuests;
	// 任务完成后的奖励
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACollectableEntity> CollectableEntityClass;
	// 分配任务
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AssignQuest(AMyPaperZDCharacter *Player, const FQuest &Quest);

	ANPC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// 送礼物给NPC
	void ReceiveGift(UItem *GiftItem);

	// 生成物品
	void SpawnItemForPlayer(AMyPaperZDCharacter *Player, TSubclassOf<ACollectableEntity> NameOfCollectableEntityClass);
	// 获取NPC的碰撞盒
	UBoxComponent *GetPlayerInteractionBox(AMyPaperZDCharacter *Player);
protected:
	FRandomStream RandomStream;// 随机数生成器
	bool bIsDialogueVisible;// 对话可见性状态
	bool bQuestCompleted;// 任务完成状态
	bool bHasGivenAppleToday;
	int32 LastGiftDay;
	ACGameMode *GameMode;
	FDateTime LastGiftDate;
	// 好感度相关
	int32 Favorability;
	int32 FavorabilityLevel;
	void IncreaseFavorability(int value = 1);
	void CheckFavorabilityLevel();

	// 用于NPC随机移动
	void MoveRandomly(float DeltaTime);

	void UpdateAnimation();

	// 随机选择一个对话字符串并显示
	void DisplayRandomDialogue(int LinesId);

	// 检测玩家是否靠近并触发对话
	virtual void CheckForPlayerInteractionBox();

	// 完成任务
	int CheckCompleteQuest();
};
