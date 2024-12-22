#include "AnimalCharacter.h"
#include "Kismet/GameplayStatics.h"

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
	//调试信息
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Animal eat food!")));
	//喂食后开始产出产品
	IsFed = true;
	//播放声音
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EatSound, GetActorLocation());
	//设置产出产品计时器
	GetWorldTimerManager().SetTimer(SpawnProductTimer, this, &AAnimalCharacter::OnSpawnProductTimerTimerTimeout,
		1.0f, false, SpawnProductTime);
}

void AAnimalCharacter::SpawnProduct()
{
	if (!IsFed || HadSpawnedProduct || !CanSpawnProduct)
		return;
	//由时间管理部分在每天的开始设置IsFed为false,HadSpawnedProduct为false
	HadSpawnedProduct = true;
	CanSpawnProduct = false;
	//产出产品
	FVector Location = GetActorLocation();
	//远离player 30 生成
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector Direction = (Location - PlayerLocation).GetSafeNormal();
	Location += Direction * 20;
	//生成产品
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Animal produce product!")));
	ACollectableEntity* Product = GetWorld()->SpawnActor<ACollectableEntity>(ProductClass, Location, FRotator::ZeroRotator);
	//播放声音
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProduceSound, GetActorLocation());

	////产出产品
	//switch (Type) {
	//	case AnimalType::Chicken:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Chicken produce egg!")));
	//		//产出鸡蛋
	//		break;
	//	case AnimalType::Cow:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Cow produce milk!")));
	//		//产出牛奶
	//		break;
	//	//case AnimalType::Pig:
	//	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Pig produce ?")));
	//	//	//产出猪,废弃
	//	//	break;
	//	case AnimalType::Sheep:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Sheep produce wool!")));
	//		//产出羊毛
	//		break;
	//}
}
