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

#include "PlayerUI.h"
#include "StardrewGameInstance.h"
#include "CollectableEntity.h"
#include "AnimalCharacter.h"
#include "FishingWidget.h"
#include "Inventory.h"
#include "SkillStates.h"
#include "FarmLand.h"


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
	Plant
};


UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	FSpawnFishDelegate SpawnFishDelegate;
	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	//MiniMap���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* MiniMapSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* MiniMapCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PlayerIndicatorSprite;

	//������ײ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBoxLeft;

	//����
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
	UFishingWidget* FishingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBackPackWidget* BackPackWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurrentUsingItemWidget* CurrentUsingItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* CameraDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* SwitchSkillAction;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceSide;

	//�ڿ󶯻�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* MineAnimSequenceSide;

	//��ˮ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* WaterAnimSequenceSide;

	//���ض���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HoeAnimSequenceSide;

	//���㶯��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* FishAnimSequenceSide;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* InteractAnimSequenceSide;

	//UI����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerUI> PlayerUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPlayerUI* PlayerUIWidget;

	//��Ʒ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventory* PlayerInventory;

	//ʵ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStardrewGameInstance* SDGameInstance;

	//����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkillStates* PlayerSkill;

	//��Ч
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PickSound;

	//�ƶ��ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 300.0f;

	//�ƶ�����
	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	//�Ƿ�����ƶ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	//�Ƿ���Ի���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanInteract = true;

	//�Ƿ�ƣ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsTired = false;

	//�Ƿ������ܲ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Running = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MiniMapEnabled = true;

	//������������
	FZDOnAnimationOverrideEndSignature OnInteractOverrideEndDelegate;


	// �洢��ҵ�ǰ�ĳ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerDirection PlayerDirection;

	// �洢��ҵ�ǰ��״̬
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerState CurrentPlayerState;


	//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Stamina = 100;

	//�ȼ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Level = 1;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Exp = 0;

	//���ɵĸ���
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFarmLand> FarmLandActorToSpawn;

	//���ɵ�����
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACrop> CarrotToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACrop> WheatToSpawn;

	AMyPaperZDCharacter();

	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	//�ƶ�
	void Move(const FInputActionValue& Value);

	//����
	void Chop();

	//�ڿ�
	void Mine();

	//��ˮ
	void Water();

	//����
	void Hoe();

	//ʹ����Ʒ
	void UseItem(const FInputActionValue& Value);

	//�л���Ʒ
	void SwitchItem(const FInputActionValue& Value);

	//����
	void Fish(const FInputActionValue& Value);

	//����
	void Run(const FInputActionValue& Value);

	//����
	void Interact(const FInputActionValue& Value);

	//���
	void CameraChangeUp(const FInputActionValue& Value);

	void CameraChangeDown(const FInputActionValue& Value);

	void Inventory(const FInputActionValue& Value);

	//�л�����
	void SwitchSkill(const FInputActionValue& Value);

	//����ģʽ����
	void PullRod(const FInputActionValue& Value);
	
	//��������
	void UpdateStamina(int Value);

	//���½�Ǯ
	//void UpdateGold(int Value);

	//���µȼ�
	void UpdateLevel(int ExValue);

	//��������
	void OnInteractOverrideAnimEnd(bool bCompleted);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������ײ�п�ʼ�ص�
	UFUNCTION()
	void InteractBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//������ײ�н����ص�
	UFUNCTION(BlueprintCallable)
	void EnableInteractBox(bool Enabled);//���û�����ײ��


	void CollectItem(UItem *ItemData);//�ռ���Ʒ

	void ActivatePlayer(bool IsActivate);//�������

	void FishGame();//����

	void FishGameTick();//������Ϸ

	std::vector<FVector> FarmLandLocationList;

	void SetScreenBrightness(float Brightness);//������Ļ����

	void SetMiniMapEnabled(bool Enabled);//����С��ͼ�Ƿ�ɼ�

	float CurrentBrightness = 0.0f;//��ǰ��Ļ����

	FTimerHandle Timer;
	FTimerHandle Timer1;
};
