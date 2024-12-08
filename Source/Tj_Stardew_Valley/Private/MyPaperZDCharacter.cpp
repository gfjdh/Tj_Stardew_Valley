#include "MyPaperZDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h" 


AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* DefaultCapsule = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("CollisionCylinder")));
	if (DefaultCapsule)
	{
		DefaultCapsule->InitCapsuleSize(16.0f, 16.0f);
	}

	// 创建一个 SpringArm 组件，并将其设置为 CapsuleComp 的子组件
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	// 设置 SpringArm 在 Z 轴方向旋转 -90 度
	SpringArm->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));

	// 创建一个 Camera 组件，并将其设置为 SpringArm 的子组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// 设置投射模式为正交
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	// 设置正交宽度为512
	Camera->OrthoWidth = 300.0f;

	GetSprite()->SetupAttachment(RootComponent);
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	// 加载默认指定的 uasset 文件
	static ConstructorHelpers::FObjectFinder<UObject> PlayerFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/idle_down/idle_down_at.idle_down_at'"));
	if (PlayerFlipbook.Succeeded())
	{
		GetSprite()->SetFlipbook(Cast<UPaperFlipbook>(PlayerFlipbook.Object));
	}

	// 加载输入上下文和移动动作
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextFinder(TEXT("InputMappingContext'/Game/Input/Input_Context.Input_Context'"));
	if (InputMappingContextFinder.Succeeded())
	{
		InputMappingContext = InputMappingContextFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("InputAction'/Game/Input/Input_Move.Input_Move'"));
	if (MoveActionFinder.Succeeded())
	{
		MoveAction = MoveActionFinder.Object;
	}

	// 加载行走和待机动画
	static ConstructorHelpers::FObjectFinder<UObject> WalkUpFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/walk_up/walk_up_at.walk_up_at'"));
	if (WalkUpFlipbook.Succeeded())
	{
		WalkUpAnimation = Cast<UPaperFlipbook>(WalkUpFlipbook.Object);
	}

	static ConstructorHelpers::FObjectFinder<UObject> WalkDownFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/walk_down/walk_down_at.walk_down_at'"));
	if (WalkDownFlipbook.Succeeded())
	{
		WalkDownAnimation = Cast<UPaperFlipbook>(WalkDownFlipbook.Object);
	}

	static ConstructorHelpers::FObjectFinder<UObject> WalkSideFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/walk_side/walk_side_at.walk_side_at'"));
	if (WalkSideFlipbook.Succeeded())
	{
		WalkSideAnimation = Cast<UPaperFlipbook>(WalkSideFlipbook.Object);
	}

	static ConstructorHelpers::FObjectFinder<UObject> IdleUpFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/idle_up/idle_up_at.idle_up_at'"));
	if (IdleUpFlipbook.Succeeded())
	{
		IdleUpAnimation = Cast<UPaperFlipbook>(IdleUpFlipbook.Object);
	}

	static ConstructorHelpers::FObjectFinder<UObject> IdleDownFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/idle_down/idle_down_at.idle_down_at'"));
	if (IdleDownFlipbook.Succeeded())
	{
		IdleDownAnimation = Cast<UPaperFlipbook>(IdleDownFlipbook.Object);
	}

	static ConstructorHelpers::FObjectFinder<UObject> IdleSideFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/idle_side/idle_side_at.idle_side_at'"));
	if (IdleSideFlipbook.Succeeded())
	{
		IdleSideAnimation = Cast<UPaperFlipbook>(IdleSideFlipbook.Object);
	}


	// 设置步高为0
	GetCharacterMovement()->MaxStepHeight = 0.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}


void AMyPaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (CanMove) {
		if (MovementDirection.Length() > 0.0f) {
			if (MovementDirection.Length() > 1.0f) {
				MovementDirection.Normalize();
			}
			FVector2D DistanceToMove = MovementDirection * MoveSpeed * DeltaTime;
			FVector CurrentLocation = GetActorLocation();
			FVector NewLocation = FVector(CurrentLocation.X + DistanceToMove.X, CurrentLocation.Y + (-1) * DistanceToMove.Y, CurrentLocation.Z);
		}
	}*/
	FVector PlayerLocation = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Location: X=%f, Y=%f, Z=%f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z));
}


void AMyPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPaperZDCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyPaperZDCharacter::StopMove);
	}
}


void AMyPaperZDCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (CanMove)
	{
		if (abs(MoveVector.Y) > 0.0f)
		{
			if (MoveVector.Y > 0.0f)
			{
				GetSprite()->SetFlipbook(WalkUpAnimation);
			}
			else
			{
				GetSprite()->SetFlipbook(WalkDownAnimation);
			}

			AddMovementInput(GetActorRightVector(), MoveVector.Y * (-1));
		}
		else if (abs(MoveVector.X) > 0.0f)
		{
			GetSprite()->SetFlipbook(WalkSideAnimation);
			if (MoveVector.X > 0.0f)
			{
				GetSprite()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
			else
			{
				GetSprite()->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
			}

			AddMovementInput(GetActorForwardVector(), MoveVector.X);
		}
	}
}

void AMyPaperZDCharacter::StopMove()
{
	MovementDirection = FVector2D::ZeroVector;
	if (GetSprite()->GetFlipbook() == WalkUpAnimation)
	{
		GetSprite()->SetFlipbook(IdleUpAnimation);
	}
	else if (GetSprite()->GetFlipbook() == WalkDownAnimation)
	{
		GetSprite()->SetFlipbook(IdleDownAnimation);
	}
	else if (GetSprite()->GetFlipbook() == WalkSideAnimation)
	{
		GetSprite()->SetFlipbook(IdleSideAnimation);
	}
}
