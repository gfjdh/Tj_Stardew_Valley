#include "MyPaperZDCharacter.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ���� PaperZD �Դ��� CollisionCylinder
	UCapsuleComponent* DefaultCapsule = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("CollisionCylinder")));
	if (DefaultCapsule)
	{
		DefaultCapsule->InitCapsuleSize(0.0f, 0.0f);
	}

	// ����һ�� CapsuleComp ���������������Ϊ�����
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	// ���� CapsuleComp �Ĵ�СΪ 10*10
	CapsuleComp->InitCapsuleSize(10.0f, 10.0f);

	// ����һ�� SpringArm ���������������Ϊ CapsuleComp �������
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

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

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PlayerAnimation(TEXT("/Game/Assets/Player/Player_Animation/idle_down"));
	if (PlayerAnimation.Succeeded())
	{
		PlayerSprite->SetFlipbook(PlayerAnimation.Object);
	}
}
