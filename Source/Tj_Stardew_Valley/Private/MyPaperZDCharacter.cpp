#include "MyPaperZDCharacter.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 忽略 PaperZD 自带的 CollisionCylinder
	UCapsuleComponent* DefaultCapsule = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("CollisionCylinder")));
	if (DefaultCapsule)
	{
		DefaultCapsule->InitCapsuleSize(0.0f, 0.0f);
	}

	// 创建一个 CapsuleComp 组件，并将其设置为根组件
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	// 设置 CapsuleComp 的大小为 10*10
	CapsuleComp->InitCapsuleSize(10.0f, 10.0f);

	// 创建一个 SpringArm 组件，并将其设置为 CapsuleComp 的子组件
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	// 创建一个 Camera 组件，并将其设置为 SpringArm 的子组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// 设置投射模式为正交
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	// 设置正交宽度为512
	Camera->OrthoWidth = 300.0f;

	// 创建一个 PaperFlipbookComponent 组件，并将其设置为根组件
	PlayerSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerSprite"));
	PlayerSprite->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PlayerAnimation(TEXT("/Game/Assets/Player/Player_Animation/idle_down"));
	if (PlayerAnimation.Succeeded())
	{
		PlayerSprite->SetFlipbook(PlayerAnimation.Object);
	}
}
