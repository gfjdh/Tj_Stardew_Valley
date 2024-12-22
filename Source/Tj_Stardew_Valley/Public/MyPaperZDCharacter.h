#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDAnimationComponent.h"
#include "Components/PostProcessComponent.h"
#include "Engine/World.h"

#include "Components/BoxComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "Components/SceneCaptureComponent2D.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundBase.h"
#include "BackPackWidget.h"
#include "CurrentUsingItemWidget.h"
#include "DayStateFilterWidget.h"
#include "CookWidget.h"
#include "MainMenuWidget.h"

#include "PlayerUI.h"
#include "StardrewGameInstance.h"
#include "CollectableEntity.h"
#include "AnimalCharacter.h"
#include "FishingWidget.h"
#include "Inventory.h"
#include "SkillStates.h"
#include "FarmLand.h"
#include "TaskWidget.h"
#include "CSkillWidget.h"


#include "MyPaperZDCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnFishDelegate);

UENUM(BlueprintType)
enum class EPlayerDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle,
	Walk,
	Chop,
	Mine,
	Water,
	Hoe,
	Fish,
	Interact,
	InFishingGame,
	BackPackOpened,
	Plant,
	Cook,
	Task,
	Heal,
	Fert
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<int32> RequiredItemIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int32 RewardGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsCompleted;
};


UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	FSpawnFishDelegate SpawnFishDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACGameMode* GameMode;
	//基本组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	//MiniMap组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* MiniMapSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* MiniMapCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PlayerIndicatorSprite;

	//互动碰撞盒
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxLeft;

	//输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* UseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SwitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* FishAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* PullRodAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* CheckTaskAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFishingWidget* FishingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackPackWidget* BackPackWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurrentUsingItemWidget* CurrentUsingItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDayStateFilterWidget* DayStateFilterWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTimeWidget* TimeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCookWidget* CookWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCookWidget* CraftWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTaskWidget* TaskWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SkillAction;

	//砍树动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceSide;

	//挖矿动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceSide;

	//浇水动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceSide;

	//铲地动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceSide;

	//钓鱼动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceSide;

	//互动动画
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceSide;

	//UI设置
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerUI> PlayerUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPlayerUI* PlayerUIWidget;

	//物品栏设置
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventory* PlayerInventory;

	//实例
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStardrewGameInstance* SDGameInstance;

	//技能
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkillStates* PlayerSkill;

	//技能buff
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Skilling=0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<USkillWidget> SkillWidgetClass;

	//UPROPERTY()
	//USkillWidget* SkillWidget;

	//音效
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PickSound;

	//移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 300.0f;

	//移动方向
	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	//是否可以移动
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	//是否可以互动
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanInteract = true;

	//是否疲劳
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsTired = false;

	//是否正在跑步
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Running = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MiniMapEnabled = true;

	//动画结束代理
	FZDOnAnimationOverrideEndSignature OnInteractOverrideEndDelegate;


	// 存储玩家当前的朝向
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerDirection PlayerDirection;

	// 存储玩家当前的状态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerState CurrentPlayerState;


	//耐力
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Stamina = 100;

	//等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Level = 1;

	//经验
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Exp = 0;

	//生成的耕地
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFarmLand> FarmLandActorToSpawn;

	//生成的作物
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACrop> CarrotToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACrop> WheatToSpawn;

	AMyPaperZDCharacter();

	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	//移动
	void Move(const FInputActionValue& Value);

	//砍树
	void Chop();

	//挖矿
	void Mine();

	//浇水
	void Water();

	//铲地
	void Hoe();

	//使用物品
	void UseItem(const FInputActionValue& Value);

	//切换物品
	void SwitchItem(const FInputActionValue& Value);

	//钓鱼
	void Fish(const FInputActionValue& Value);

	//奔跑
	void Run(const FInputActionValue& Value);

	//互动
	void Interact(const FInputActionValue& Value);

	//相机
	void CameraChangeUp(const FInputActionValue& Value);

	void CameraChangeDown(const FInputActionValue& Value);

	void Inventory(const FInputActionValue& Value);

	//展示技能面板
	//void DisplaySkillBoard(const FInputActionValue& Value);

	//钓鱼模式按键
	void PullRod(const FInputActionValue& Value);
	
	//查看任务列表
	void CheckTask(const FInputActionValue& Value);

	//更新耐力
	void UpdateStamina(int Value);


	//动画结束
	void OnInteractOverrideAnimEnd(bool bCompleted);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//互动碰撞盒开始重叠
	UFUNCTION()
	void InteractBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//互动碰撞盒结束重叠
	UFUNCTION(BlueprintCallable)
	void EnableInteractBox(bool Enabled);//启用互动碰撞盒


	void CollectItem(UItem *ItemData);//收集物品

	void ActivatePlayer(bool IsActivate);//激活玩家

	void FishGame();//钓鱼

	void FishGameTick();//钓鱼游戏

	std::vector<FVector> FarmLandLocationList;

	void SetScreenBrightness(float Brightness);//设置屏幕亮度

	void SetMiniMapEnabled(bool Enabled);//设置小地图是否可见

	// 任务列表
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FQuest> Quests;

	// 接收任务
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ReceiveQuest(const FQuest &NewQuest);

	// 完成任务
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CompleteQuest(int32 QuestIndex);

	void CheckAndCompleteQuest();

	float CurrentBrightness = 0.0f;//当前屏幕亮度

	void SetTimeWidgetImage();

	FTimerHandle Timer;
	FTimerHandle Timer1;

	// 指向用户界面类的指针
	UPROPERTY(EditAnywhere,BluePrintReadWrite, Category = "UI")
	TSubclassOf<UCSkillWidget> SkillWidgetClass;

	// 指向当前用户界面实例的指针
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "UI")
	UCSkillWidget* SkillWidgetInstance;

	//用来开关技能面板
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SkillBoardIsOpen=0;

	UFUNCTION()
	void DisplaySkillBoard();

	//技能面版各种按钮触发事件
	UFUNCTION()
	void OnCookSkillLevel1Clicked();

	UFUNCTION()
	void OnCookSkillLevel2Clicked();

	UFUNCTION()
	void OnFarmingSkillLevel1Clicked();

	UFUNCTION()
	void OnFarmingSkillLevel2Clicked();

	UFUNCTION()
	void OnToolSkillLevel1Clicked();

	UFUNCTION()
	void OnToolSkillLevel2Clicked();
};