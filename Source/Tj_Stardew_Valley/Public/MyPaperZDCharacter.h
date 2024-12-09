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

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Components/BoxComponent.h"


#include "MyPaperZDCharacter.generated.h"



UENUM(BlueprintType)
enum class EPlayerDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};


UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* ChopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* ChopAnimSequenceSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 300.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanInteract = true;


	FZDOnAnimationOverrideEndSignature OnChopOverrideEndDelegate;



	// 存储玩家当前的朝向
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerDirection PlayerDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Stamina = 100.0f;


	AMyPaperZDCharacter();

	virtual void BeginPlay() override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Chop(const FInputActionValue& Value);

	void OnChopOverrideAnimEnd(bool bCompleted);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
