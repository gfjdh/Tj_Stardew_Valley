#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"



#include "MyPaperZDCharacter.generated.h"

UCLASS()
class TJ_STARDEW_VALLEY_API AMyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;




	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 300.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkUpAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkDownAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* WalkSideAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleUpAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleDownAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleSideAnimation;

	AMyPaperZDCharacter();

	virtual void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void StopMove();

	void Interact(const FInputActionValue& Value);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
