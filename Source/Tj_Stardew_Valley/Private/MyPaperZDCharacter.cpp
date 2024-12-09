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

	//GetSprite()->SetupAttachment(RootComponent);
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));


	/*static ConstructorHelpers::FClassFinder<UPaperZDAnimInstance> AnimBPClass(TEXT("/Game/Assets/Player/BP_PlayerAnim"));
	if (AnimBPClass.Succeeded())
	{
		GetAnimationComponent()->SetAnimInstanceClass(AnimBPClass.Class);//写入会导致虚幻无法正常启动
	}*/


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

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionFinder(TEXT("InputAction'/Game/Input/Input_Interaction.Input_Interaction'"));
	if (InteractionFinder.Succeeded())
	{
		Interaction = InteractionFinder.Object;
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
	FVector PlayerLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Location: X=%f, Y=%f, Z=%f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z));
}


void AMyPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPaperZDCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyPaperZDCharacter::StopMove);
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Triggered, this, &AMyPaperZDCharacter::Interact);
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Completed, this, &AMyPaperZDCharacter::StopMove);
	}
}


void AMyPaperZDCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (CanMove)
	{
		if (FMath::Abs(MoveVector.Y) > 0.0f)
		{
			if (MoveVector.Y > 0.0f)
			{
				PlayerDirection = EPlayerDirection::Up;
			}
			else
			{
				PlayerDirection = EPlayerDirection::Down;
			}

			AddMovementInput(GetActorRightVector(), -MoveVector.Y);
		}
		else if (FMath::Abs(MoveVector.X) > 0.0f)
		{

			if (MoveVector.X > 0.0f)
			{
				GetSprite()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
				PlayerDirection = EPlayerDirection::Right;
			}
			else
			{
				GetSprite()->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
				PlayerDirection = EPlayerDirection::Left;
			}

			AddMovementInput(GetActorForwardVector(), MoveVector.X);
		}
	}
}

void AMyPaperZDCharacter::StopMove()
{
	MovementDirection = FVector2D::ZeroVector;
	if (!CanMove)
	{
		CanMove = true;
	}
}

void AMyPaperZDCharacter::Interact(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (CanMove)
		{
			CanMove = false;
		}
	}
}