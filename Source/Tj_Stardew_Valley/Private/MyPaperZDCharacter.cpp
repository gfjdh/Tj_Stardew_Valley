#include "MyPaperZDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Actor.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// ���� PaperZD �Դ��� CollisionCylinder
	UCapsuleComponent* DefaultCapsule = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("CollisionCylinder")));
	if (DefaultCapsule)
	{
		DefaultCapsule->InitCapsuleSize(16.0f, 16.0f);
	}

	// ����һ�� CapsuleComp ���������������Ϊ�����
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	// ���� CapsuleComp �Ĵ�СΪ 10*10
	CapsuleComp->InitCapsuleSize(16.0f, 16.0f);


	// ����һ�� SpringArm ���������������Ϊ CapsuleComp �������
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	// ���� SpringArm �� Z �᷽����ת -90 ��
	SpringArm->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));

	// ����һ�� Camera ���������������Ϊ SpringArm �������
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// ����Ͷ��ģʽΪ����
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	// �����������Ϊ512
	Camera->OrthoWidth = 300.0f;

	// ����һ�� PaperFlipbookComponent ���������������Ϊ�����
	PlayerSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerSprite"));
	PlayerSprite->SetupAttachment(RootComponent);
	PlayerSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	// ����Ĭ��ָ���� uasset �ļ�
	static ConstructorHelpers::FObjectFinder<UObject> PlayerFlipbook(TEXT("PaperFlipbook'/Game/Assets/Player/Player_Animation/idle_down/idle_down_at.idle_down_at'"));
	if (PlayerFlipbook.Succeeded())
	{
		PlayerSprite->SetFlipbook(Cast<UPaperFlipbook>(PlayerFlipbook.Object));
	}

	// �������������ĺ��ƶ�����
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

	// �������ߺʹ�������
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
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("MoveVector: %s"), *MoveVector.ToString()));

	if (CanMove)
	{
		if (abs(MoveVector.Y) > 0.0f)
		{

			if (MoveVector.Y > 0.0f)
			{
				PlayerSprite->SetFlipbook(WalkUpAnimation);
			}
			else
			{
				PlayerSprite->SetFlipbook(WalkDownAnimation);
			}

			float DeltaTime = GetWorld()->DeltaTimeSeconds;
			FVector CurrentLocation = GetActorLocation();
			FVector DistanceToMove = GetActorRightVector() * MoveSpeed * MoveVector.Y * DeltaTime * (-1);
			FVector NewLocation = CurrentLocation + DistanceToMove;
			SetActorLocation(NewLocation);
		}
		else if (abs(MoveVector.X) > 0.0f)
		{
			PlayerSprite->SetFlipbook(WalkSideAnimation);
			if (MoveVector.X > 0.0f)
			{
				PlayerSprite->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
			else
			{
				PlayerSprite->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
			}
			float DeltaTime = GetWorld()->DeltaTimeSeconds;
			FVector CurrentLocation = GetActorLocation();
			FVector DistanceToMove = GetActorForwardVector() * MoveSpeed * MoveVector.X * DeltaTime;
			FVector NewLocation = CurrentLocation + DistanceToMove;
			SetActorLocation(NewLocation);
		}
	}
}

void AMyPaperZDCharacter::StopMove()
{
	if (PlayerSprite->GetFlipbook() == WalkUpAnimation)
	{
		PlayerSprite->SetFlipbook(IdleUpAnimation);
	}
	else if (PlayerSprite->GetFlipbook() == WalkDownAnimation)
	{
		PlayerSprite->SetFlipbook(IdleDownAnimation);
	}
	else if (PlayerSprite->GetFlipbook() == WalkSideAnimation)
	{
		PlayerSprite->SetFlipbook(IdleSideAnimation);
	}
}
