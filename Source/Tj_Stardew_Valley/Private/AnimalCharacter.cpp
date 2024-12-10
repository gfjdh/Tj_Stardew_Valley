#include "AnimalCharacter.h"

AAnimalCharacter::AAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	IsAlive = true;
	CanMove = true;
	IsFed = false;
}

void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAlive) {
		if (CanMove) {
			//如果还未开始移动,则随机方向
			if (!MoveStarted) {
				switch (FMath::RandRange(0, 3)) {
					case 0:
						MovementDirection = Direction::Up;
						break;
					case 1:
						MovementDirection = Direction::Down;
						break;
					case 2:
						MovementDirection = Direction::Left;
						break;
					case 3:
						MovementDirection = Direction::Right;
						break;
				}
			}
			//移动
			Move();
		}
	}
}

void AAnimalCharacter::Move()
{
	if (IsAlive) {
		if (CanMove) {
			float Neg = 1.0f;
			
			//设置动物朝向
			if (MovementDirection == Direction::Right || MovementDirection == Direction::Left)
			{
				AnimalDirection = MovementDirection;
			}
			//设置动物移动方向
			if (MovementDirection == Direction::Left || MovementDirection == Direction::Down)
			{
				Neg = -1.0f;
			}
			else
			{
				Neg = 1.0f;
			}
			//更新朝向贴图
			UpdateDirection();
			//根据移动方向移动
			if (MovementDirection == Direction::Up || MovementDirection == Direction::Down)
			{
				AddMovementInput(GetActorRightVector(), Neg);
			}
			else
			{
				AddMovementInput(GetActorForwardVector(), Neg);
			}
			//只在移动开始第一次设置计时器
			if (MoveStarted)
				return;

			//设置移动持续时间
			GetWorldTimerManager().SetTimer(MoveDurationTimer, this, &AAnimalCharacter::OnMoveDurationTimerTimeout,
				1.0f, false, MovementDuration);
			//设置移动冷却
			GetWorldTimerManager().SetTimer(MoveCoolDownTimer, this, &AAnimalCharacter::OnMoveCoolDownTimerTimeout, 
				1.0f , false, MovementCoolDown);
			MoveStarted = true;
		}
	}
}

void AAnimalCharacter::OnMoveCoolDownTimerTimeout()
{
	if (IsAlive)
	{
		CanMove = true;
		MoveStarted = false;
	}
}

void AAnimalCharacter::OnMoveDurationTimerTimeout()
{
	if (IsAlive)
	{
		CanMove = false;
	}
}

void AAnimalCharacter::UpdateDirection()
{
	if (AnimalDirection == Direction::Left)
	{
		GetSprite()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	else
	{
		GetSprite()->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
	}
}
