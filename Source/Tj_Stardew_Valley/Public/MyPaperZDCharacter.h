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


#include "PlayerUI.h"


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
	Hoe
};

UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

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
	UInputAction* ChopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MineAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* WaterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* HoeAction;

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerUI> PlayerUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPlayerUI* PlayerUIWidget;


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

	//��Ǯ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Gold = 0;

	//�ȼ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Level = 1;

	AMyPaperZDCharacter();

	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//�ƶ�
	void Move(const FInputActionValue& Value);

	//����
	void Chop(const FInputActionValue& Value);

	//�ڿ�
	void Mine(const FInputActionValue& Value);

	//��ˮ
	void Water(const FInputActionValue& Value);

	//����
	void Hoe(const FInputActionValue& Value);

	//��������
	void UpdateStamina(int Value);

	//���½�Ǯ
	//void UpdateGold(int Value);

	//���µȼ�
	//void UpdateLevel(int Value);

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
	void EnableInteractBox(bool Enabled);
};
