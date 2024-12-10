#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "Engine/TimerHandle.h"
#include "PaperFlipbookComponent.h"

#include "AnimalCharacter.generated.h"

UENUM(BlueprintType)
enum class Direction : uint8
{
	Up,
	Down,
	Left,
	Right
};

UENUM(BlueprintType)
enum class AnimalType : uint8
{
	Chicken,
	Cow,
	Pig,
	Sheep
};

UCLASS()
class TJ_STARDEW_VALLEY_API AAnimalCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
//���캯�����麯������
public:
	AAnimalCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
//��Ա����
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAlive = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsFed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool MoveStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementCoolDown = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AnimalType Type;

	//����(�����)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	Direction AnimalDirection = Direction::Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	Direction MovementDirection;

	FTimerHandle MoveCoolDownTimer;
	FTimerHandle MoveDurationTimer;


//��Ա����
public:
	void Move();
	void OnMoveCoolDownTimerTimeout();
	void OnMoveDurationTimerTimeout();
	void UpdateDirection();
};
