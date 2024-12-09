#pragma once

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
#include "Components/BoxComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundBase.h"


#include "PlayerUI.h"
#include "StardrewGameInstance.h"
#include "CollectableEntity.h"
#include "AnimalCharacter.h"
#include "FishSpot.h"
#include "FishingWidget.h"

#include "MyPaperZDCharacter.generated.h"



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
	InFishingGame
};


UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	//基本组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

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
	UInputAction* ChopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MineAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* WaterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* HoeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* FishAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* PullRodAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFishingWidget* FishingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraDownAction;

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

	//实例
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStardrewGameInstance* SDGameInstance;

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

	AMyPaperZDCharacter();

	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//移动
	void Move(const FInputActionValue& Value);

	//砍树
	void Chop(const FInputActionValue& Value);

	//挖矿
	void Mine(const FInputActionValue& Value);

	//浇水
	void Water(const FInputActionValue& Value);

	//铲地
	void Hoe(const FInputActionValue& Value);

	//钓鱼
	void Fish(const FInputActionValue& Value);

	//奔跑
	void Run(const FInputActionValue& Value);

	//互动
	void Interact(const FInputActionValue& Value);

	//相机
	void CameraChangeUp(const FInputActionValue& Value);

	void CameraChangeDown(const FInputActionValue& Value);


	//钓鱼模式按键
	void PullRod(const FInputActionValue& Value);

	//更新耐力
	void UpdateStamina(int Value);

	//更新金钱
	//void UpdateGold(int Value);

	//更新等级
	void UpdateLevel(int ExValue);

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
	void EnableInteractBox(bool Enabled);


	void CollectItem(CollectableType ItemType);

	void ActivatePlayer(bool IsActivate);

	void FishGame();
};
