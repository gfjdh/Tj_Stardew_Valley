#include "MyPaperZDCharacter.h"
#include "TreeStump.h"
#include "Ores.h"
#include "Crop.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// 设置默认碰撞体
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

	// 创建互动碰撞盒
	InteractionBoxUp = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBoxUp"));
	InteractionBoxUp->SetupAttachment(RootComponent);
	InteractionBoxUp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	InteractionBoxDown = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBoxDown"));
	InteractionBoxDown->SetupAttachment(RootComponent);
	InteractionBoxDown->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractionBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBoxRight"));
	InteractionBoxRight->SetupAttachment(RootComponent);
	InteractionBoxRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractionBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBoxLeft"));
	InteractionBoxLeft->SetupAttachment(RootComponent);
	InteractionBoxLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 设置角色的默认朝向
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));





	/*static ConstructorHelpers::FClassFinder<UPaperZDAnimInstance> AnimBPClass(TEXT("/Game/Assets/Player/BP_PlayerAnim"));
	if (AnimBPClass.Succeeded())
	{
		GetAnimationComponent()->SetAnimInstanceClass(AnimBPClass.Class);//写入会导致虚幻无法正常启动
	}*/

	// 设置默认移动方向
	PlayerDirection = EPlayerDirection::Down;

	// 设置默认玩家状态
	CurrentPlayerState = EPlayerState::Idle;

	// 加载输入上下文和移动动作
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextFinder(TEXT("InputMappingContext'/Game/Input/Input_Context.Input_Context'"));
	if (InputMappingContextFinder.Succeeded())
	{
		InputMappingContext = InputMappingContextFinder.Object;
	}

	// 加载输入动作
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("InputAction'/Game/Input/Input_Move.Input_Move'"));
	if (MoveActionFinder.Succeeded())
	{
		MoveAction = MoveActionFinder.Object;
	}

	// 加载砍树输入
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionFinder(TEXT("InputAction'/Game/Input/Input_Chop.Input_Chop'"));
	if (InteractionFinder.Succeeded())
	{
		ChopAction = InteractionFinder.Object;
	}

	// 加载挖矿输入
	static ConstructorHelpers::FObjectFinder<UInputAction> MineFinder(TEXT("InputAction'/Game/Input/Input_Mine.Input_Mine'"));
	if (MineFinder.Succeeded())
	{
		MineAction = MineFinder.Object;
	}

	// 加载浇水输入
	static ConstructorHelpers::FObjectFinder<UInputAction> WaterFinder(TEXT("InputAction'/Game/Input/Input_Water.Input_Water'"));
	if (WaterFinder.Succeeded())
	{
		WaterAction = WaterFinder.Object;
	}

	// 加载铲地输入
	static ConstructorHelpers::FObjectFinder<UInputAction> HoeFinder(TEXT("InputAction'/Game/Input/Input_Hoe.Input_Hoe'"));
	if (HoeFinder.Succeeded())
	{
		HoeAction = HoeFinder.Object;
	}

	// 设置步高为0
	GetCharacterMovement()->MaxStepHeight = 0.0f;

	// 设置默认玩家控制器
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 添加输入上下文
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// 绑定动画结束代理
	OnInteractOverrideEndDelegate.BindUObject(this, &AMyPaperZDCharacter::OnInteractOverrideAnimEnd);
	InteractionBoxUp->OnComponentBeginOverlap.AddDynamic(this, &AMyPaperZDCharacter::InteractBoxOverlapBegin);
	InteractionBoxDown->OnComponentBeginOverlap.AddDynamic(this, &AMyPaperZDCharacter::InteractBoxOverlapBegin);
	InteractionBoxRight->OnComponentBeginOverlap.AddDynamic(this, &AMyPaperZDCharacter::InteractBoxOverlapBegin);
	InteractionBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &AMyPaperZDCharacter::InteractBoxOverlapBegin);

	SDGameInstance = Cast<UStardrewGameInstance>(GetGameInstance());
	if (SDGameInstance)
	{
		Stamina = SDGameInstance->Stamina;
	}

	// 创建玩家UI
	if (PlayerUIClass)
	{
		PlayerUIWidget = CreateWidget <UPlayerUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerUIClass);
		if (PlayerUIWidget)
		{
			PlayerUIWidget->AddToPlayerScreen();
			PlayerUIWidget->SetStamina(Stamina);
			PlayerUIWidget->SetGold(36);
			PlayerUIWidget->SetLevel(1);

		}
	}

}

// Called every frame
void AMyPaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Location: X=%f, Y=%f, Z=%f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z));
}


// Called to bind functionality to input
void AMyPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPaperZDCharacter::Move);
		EnhancedInputComponent->BindAction(ChopAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Chop);
		EnhancedInputComponent->BindAction(MineAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Mine);
		EnhancedInputComponent->BindAction(WaterAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Water);
		EnhancedInputComponent->BindAction(HoeAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Hoe);
	}
}

// 移动
void AMyPaperZDCharacter::Move(const FInputActionValue& Value)
{
	// 获取移动向量
	FVector2D MoveVector = Value.Get<FVector2D>();


	if (CanMove)
	{
		CurrentPlayerState = EPlayerState::Walk;

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

	CurrentPlayerState = EPlayerState::Idle;
}

// 砍树
void AMyPaperZDCharacter::Chop(const FInputActionValue& Value)
{
	if (CanInteract)
	{
		CurrentPlayerState = EPlayerState::Chop;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Chop!")));
		CanMove = false;
		CanInteract = false;
		EnableInteractBox(true);
		switch (PlayerDirection)
		{
			case EPlayerDirection::Up:
				GetAnimInstance()->PlayAnimationOverride(ChopAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Down:
				GetAnimInstance()->PlayAnimationOverride(ChopAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Left:
			case EPlayerDirection::Right:
				GetAnimInstance()->PlayAnimationOverride(ChopAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
		}
	}

	CurrentPlayerState = EPlayerState::Idle;
	UpdateStamina(-5);
}

// 挖矿
void AMyPaperZDCharacter::Mine(const FInputActionValue& Value)
{
	if (CanInteract)
	{
		CurrentPlayerState = EPlayerState::Mine;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Mine!")));
		CanMove = false;
		CanInteract = false;
		EnableInteractBox(true);
		switch (PlayerDirection)
		{
			case EPlayerDirection::Up:
				GetAnimInstance()->PlayAnimationOverride(MineAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Down:
				GetAnimInstance()->PlayAnimationOverride(MineAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Left:
			case EPlayerDirection::Right:
				GetAnimInstance()->PlayAnimationOverride(MineAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
		}
	}

	CurrentPlayerState = EPlayerState::Idle;
	UpdateStamina(-5);
}

// 浇水
void AMyPaperZDCharacter::Water(const FInputActionValue& Value)
{
	if (CanInteract)
	{
		CurrentPlayerState = EPlayerState::Water;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Water!")));
		CanMove = false;
		CanInteract = false;
		EnableInteractBox(true);
		switch (PlayerDirection)
		{
			case EPlayerDirection::Up:
				GetAnimInstance()->PlayAnimationOverride(WaterAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Down:
				GetAnimInstance()->PlayAnimationOverride(WaterAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Left:
			case EPlayerDirection::Right:
				GetAnimInstance()->PlayAnimationOverride(WaterAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
		}
	}

	CurrentPlayerState = EPlayerState::Idle;
	UpdateStamina(-2);
}

// 铲地
void AMyPaperZDCharacter::Hoe(const FInputActionValue& Value)
{
	if (CanInteract)
	{
		CurrentPlayerState = EPlayerState::Hoe;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hoe!")));
		CanMove = false;
		CanInteract = false;
		EnableInteractBox(true);
		switch (PlayerDirection)
		{
			case EPlayerDirection::Up:
				GetAnimInstance()->PlayAnimationOverride(HoeAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Down:
				GetAnimInstance()->PlayAnimationOverride(HoeAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Left:
			case EPlayerDirection::Right:
				GetAnimInstance()->PlayAnimationOverride(HoeAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
		}
	}

	CurrentPlayerState = EPlayerState::Idle;
	UpdateStamina(-5);
}

// 互动动画结束
void AMyPaperZDCharacter::OnInteractOverrideAnimEnd(bool bCompleted)
{
	CanMove = true;
	CanInteract = true;
	EnableInteractBox(false);
}


// 互动树开始重叠
void AMyPaperZDCharacter::InteractBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	ATreeStump* TreeStump = Cast<ATreeStump>(OtherActor);
	AOres* Ores = Cast<AOres>(OtherActor);
	ACrop* Crop = Cast<ACrop>(OtherActor);

	if (TreeStump) {
		if (CurrentPlayerState == EPlayerState::Chop) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Tree is being Chopped"));
			//TreeStump->Chop();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Not Useful Tool"));
		}
	}
	else if (Ores) {
		if (CurrentPlayerState == EPlayerState::Mine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Ores is being Mined"));
			//Ores->Mine();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Not Useful Tool"));
		}
	}

	else if (Crop) {
		if (CurrentPlayerState == EPlayerState::Water) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Crop is being Watered"));
			//Crop->Water();
		}
		else if (CurrentPlayerState == EPlayerState::Hoe) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Crop is being Hoed"));
			//Crop->Hoe();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Not Useful Tool"));
		}
	}
}



// 互动碰撞盒结束重叠
void AMyPaperZDCharacter::EnableInteractBox(bool Enabled){

	UBoxComponent* InteractionBox = InteractionBoxUp;

	switch (PlayerDirection) {
		case EPlayerDirection::Up:
			InteractionBox = InteractionBoxUp;
			break;
		case EPlayerDirection::Down:
			InteractionBox = InteractionBoxDown;
			break;
		case EPlayerDirection::Left:
			InteractionBox = InteractionBoxLeft;
			break;
		case EPlayerDirection::Right:
			InteractionBox = InteractionBoxRight;
			break;
	}

	if (Enabled) {
		InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
	else {
		InteractionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
}

void AMyPaperZDCharacter::UpdateStamina(int Value) {
	Stamina += Value;
	if (Stamina > 100) {
		Stamina = 100;
	}
	else if (Stamina < 0) {
		Stamina = 0;
	}
	PlayerUIWidget->SetStamina(Stamina);
	SDGameInstance->SetPlayerStamina(Stamina);
}


void AMyPaperZDCharacter::CollectItem(CollectableType ItemType) {
	//播放声音
	//UGameplayStatics::PlaySound2D(GetWorld(), PickSound);

	switch (ItemType) {
		case CollectableType::Potion:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Potion"));
			break;
		case CollectableType::Gold:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Gold"));
			break;
		case CollectableType::Wood:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Wood"));
			break;
		case CollectableType::Stone:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Stone"));
			break;
		case CollectableType::Ore:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Ore"));
			break;
		case CollectableType::Seed:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Seed"));
			break;
		case CollectableType::Tool:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Tool"));
			break;
		case CollectableType::Food:				
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Food"));
			break;
		case CollectableType::Crop:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Crop"));
			break;
		case CollectableType::Other:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Other"));
			break;
		default:
			break;
	}


}