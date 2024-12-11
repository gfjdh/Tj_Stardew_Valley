#include "AnimalCharacter.h"

AAnimalCharacter::AAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	IsAlive = true;
	CanMove = true;
	IsFed = false;
	MoveStarted = false;
	HadSpawnedProduct = false;
	CanSpawnProduct = false;
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
			//�����δ��ʼ�ƶ�,���������
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
			//�ƶ�
			Move();
		}
	}
}

void AAnimalCharacter::Move()
{
	if (IsAlive) {
		if (CanMove) {
			float Neg = 1.0f;
			
			//���ö��ﳯ��
			if (MovementDirection == Direction::Right || MovementDirection == Direction::Left)
			{
				AnimalDirection = MovementDirection;
			}
			//���ö����ƶ�����
			if (MovementDirection == Direction::Left || MovementDirection == Direction::Down)
			{
				Neg = -1.0f;
			}
			else
			{
				Neg = 1.0f;
			}
			//���³�����ͼ
			UpdateDirection();
			//�����ƶ������ƶ�
			if (MovementDirection == Direction::Up || MovementDirection == Direction::Down)
			{
				AddMovementInput(GetActorRightVector(), Neg);
			}
			else
			{
				AddMovementInput(GetActorForwardVector(), Neg);
			}
			//ֻ���ƶ���ʼ��һ�����ü�ʱ��
			if (MoveStarted)
				return;

			//�����ƶ�����ʱ��
			GetWorldTimerManager().SetTimer(MoveDurationTimer, this, &AAnimalCharacter::OnMoveDurationTimerTimeout,
				1.0f, false, MovementDuration);
			//�����ƶ���ȴ
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

void AAnimalCharacter::OnSpawnProductTimerTimerTimeout()
{
	if (IsAlive)
	{
		CanSpawnProduct = true;
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

void AAnimalCharacter::EatFood()
{
	//�ж�ι��ʳ�������Ƿ���ȷ
	
	//������Ϣ
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Animal eat food!")));
	//ιʳ��ʼ������Ʒ
	IsFed = true;
	
	GetWorldTimerManager().SetTimer(SpawnProductTimer, this, &AAnimalCharacter::OnSpawnProductTimerTimerTimeout,
		1.0f, false, SpawnProductTime);
}

void AAnimalCharacter::SpawnProduct()
{
	if (!IsFed || HadSpawnedProduct || !CanSpawnProduct)
		return;
	//��ʱ�����������ÿ��Ŀ�ʼ����IsFedΪfalse,HadSpawnedProductΪfalse
	HadSpawnedProduct = true;
	CanSpawnProduct = false;

	//������Ʒ
	switch (Type) {
		case AnimalType::Chicken:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Chicken produce egg!")));
			//��������
			break;
		case AnimalType::Cow:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Cow produce milk!")));
			//����ţ��
			break;
		case AnimalType::Pig:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Pig produce ?")));
			//������
			break;
		case AnimalType::Sheep:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Sheep produce wool!")));
			//������ë
			break;
	}
}