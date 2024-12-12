#include "MyPaperZDCharacter.h"
#include "TreeStump.h"
#include "Ores.h"
#include "Crop.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// ����Ĭ����ײ��
	UCapsuleComponent* DefaultCapsule = Cast<UCapsuleComponent>(GetDefaultSubobjectByName(TEXT("CollisionCylinder")));
	if (DefaultCapsule)
	{
		DefaultCapsule->InitCapsuleSize(16.0f, 16.0f);
	}

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
	// �����������Ϊ300
	Camera->OrthoWidth = 300.0f;

	// ����������ײ��
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

	// ���ý�ɫ��Ĭ�ϳ���
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));


	PlayerInventory = CreateDefaultSubobject<UInventory>(TEXT("PlayerInventory"));




	/*static ConstructorHelpers::FClassFinder<UPaperZDAnimInstance> AnimBPClass(TEXT("/Game/Assets/Player/BP_PlayerAnim"));
	if (AnimBPClass.Succeeded())
	{
		GetAnimationComponent()->SetAnimInstanceClass(AnimBPClass.Class);//д��ᵼ������޷���������
	}*/

	// ����Ĭ���ƶ�����
	PlayerDirection = EPlayerDirection::Down;

	// ����Ĭ�����״̬
	CurrentPlayerState = EPlayerState::Idle;

	// �������������ĺ��ƶ�����
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextFinder(TEXT("InputMappingContext'/Game/Input/Input_Context.Input_Context'"));
	if (InputMappingContextFinder.Succeeded())
	{
		InputMappingContext = InputMappingContextFinder.Object;
	}

	// �������붯��
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("InputAction'/Game/Input/Input_Move.Input_Move'"));
	if (MoveActionFinder.Succeeded())
	{
		MoveAction = MoveActionFinder.Object;
	}

	// ���ؿ�������
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionFinder(TEXT("InputAction'/Game/Input/Input_Chop.Input_Chop'"));
	if (InteractionFinder.Succeeded())
	{
		ChopAction = InteractionFinder.Object;
	}

	// �����ڿ�����
	static ConstructorHelpers::FObjectFinder<UInputAction> MineFinder(TEXT("InputAction'/Game/Input/Input_Mine.Input_Mine'"));
	if (MineFinder.Succeeded())
	{
		MineAction = MineFinder.Object;
	}

	// ���ؽ�ˮ����
	static ConstructorHelpers::FObjectFinder<UInputAction> WaterFinder(TEXT("InputAction'/Game/Input/Input_Water.Input_Water'"));
	if (WaterFinder.Succeeded())
	{
		WaterAction = WaterFinder.Object;
	}

	// ���ز�������
	static ConstructorHelpers::FObjectFinder<UInputAction> HoeFinder(TEXT("InputAction'/Game/Input/Input_Hoe.Input_Hoe'"));
	if (HoeFinder.Succeeded())
	{
		HoeAction = HoeFinder.Object;
	}

	// ���ص�������
	static ConstructorHelpers::FObjectFinder<UInputAction> FishFinder(TEXT("InputAction'/Game/Input/Input_Fish.Input_Fish'"));
	if (FishFinder.Succeeded())
	{
		FishAction = FishFinder.Object;
	}

	// ���ػ�������
	static ConstructorHelpers::FObjectFinder<UInputAction> InterActionFinder(TEXT("InputAction'/Game/Input/Input_Interact.Input_Interact'"));
	if (InterActionFinder.Succeeded())
	{
		InterAction = InterActionFinder.Object;
	}
	// ���ر�������
	static ConstructorHelpers::FObjectFinder<UInputAction> RunFinder(TEXT("InputAction'/Game/Input/Input_Run.Input_Run'"));
	if (RunFinder.Succeeded())
	{
		RunAction = RunFinder.Object;
	}

	// �����������
	static ConstructorHelpers::FObjectFinder<UInputAction> CameraFinder(TEXT("InputAction'/Game/Input/Input_CameraUp.Input_CameraUp'"));
	if (CameraFinder.Succeeded())
	{
		CameraUpAction = CameraFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CameraDownFinder(TEXT("InputAction'/Game/Input/Input_CameraDown.Input_CameraDown'"));
	if (CameraDownFinder.Succeeded())
	{
		CameraDownAction = CameraDownFinder.Object;
	}

	// ������Ʒ������
	static ConstructorHelpers::FObjectFinder<UInputAction> InventoryFinder(TEXT("InputAction'/Game/Input/Input_Inventory.Input_Inventory'"));
	if(InventoryFinder.Succeeded())
	{
		InventoryAction = InventoryFinder.Object;
	}

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	// ���ò���Ϊ0
	GetCharacterMovement()->MaxStepHeight = 0.0f;

	// ����Ĭ����ҿ�����
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �������������
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		//��ʾ���
		PlayerController->SetShowMouseCursor(true);

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// �󶨶�����������
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

	// �������UI
	if (PlayerUIClass)
	{
		PlayerUIWidget = CreateWidget <UPlayerUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerUIClass);
		if (PlayerUIWidget)
		{
			PlayerUIWidget->AddToPlayerScreen();
			PlayerUIWidget->SetStamina(Stamina);
			PlayerUIWidget->SetGold(SDGameInstance->GoldWealth);
			PlayerUIWidget->SetLevel(Level);
		}
	}

}

// Called every frame
void AMyPaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Player Location: X=%f, Y=%f, Z=%f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z));
	FishGameTick();
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
		EnhancedInputComponent->BindAction(FishAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Fish);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Run);
		EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Interact);
		EnhancedInputComponent->BindAction(PullRodAction, ETriggerEvent::Triggered, this, &AMyPaperZDCharacter::PullRod);
		EnhancedInputComponent->BindAction(CameraUpAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::CameraChangeUp);
		EnhancedInputComponent->BindAction(CameraDownAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::CameraChangeDown);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMyPaperZDCharacter::Inventory);
	}
}

// �ƶ�
void AMyPaperZDCharacter::Move(const FInputActionValue& Value)
{
	// ��ȡ�ƶ�����
	FVector2D MoveVector = Value.Get<FVector2D>();
	if (CurrentPlayerState == EPlayerState::InFishingGame) 
		return;

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

// ����
void AMyPaperZDCharacter::Chop(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
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

		CurrentPlayerState = EPlayerState::Idle;
		UpdateStamina(-5);
	}
}

// �ڿ�
void AMyPaperZDCharacter::Mine(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
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

		CurrentPlayerState = EPlayerState::Idle;
		UpdateStamina(-5);
	}
}

// ��ˮ
void AMyPaperZDCharacter::Water(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
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

		CurrentPlayerState = EPlayerState::Idle;
		UpdateStamina(-2);
	}
}


// ����
void AMyPaperZDCharacter::Hoe(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
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

		CurrentPlayerState = EPlayerState::Idle;
		UpdateStamina(-5);
	}
}

// ����
void AMyPaperZDCharacter::Fish(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
	if (CanInteract)
	{
		CurrentPlayerState = EPlayerState::Fish;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Fish!")));
		ActivatePlayer(false);
		EnableInteractBox(true);
		switch (PlayerDirection)
		{
			case EPlayerDirection::Up:
				GetAnimInstance()->PlayAnimationOverride(FishAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Down:
				GetAnimInstance()->PlayAnimationOverride(FishAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
			case EPlayerDirection::Left:
			case EPlayerDirection::Right:
				GetAnimInstance()->PlayAnimationOverride(FishAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
				break;
		}
	}
}

// �л����
void AMyPaperZDCharacter::CameraChangeUp(const FInputActionValue& Value)
{

	Camera->OrthoWidth += 100.0f;
	if (Camera->OrthoWidth > 550.0f)
	{
		Camera->OrthoWidth = 550.0f;
	}
}

void AMyPaperZDCharacter::CameraChangeDown(const FInputActionValue& Value)
{
	Camera->OrthoWidth -= 100.0f;
	if (Camera->OrthoWidth < 50.0f)
	{
		Camera->OrthoWidth = 50.0f;
	}
}


// ����
void AMyPaperZDCharacter::Interact(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame)
		return;
	CurrentPlayerState = EPlayerState::Interact;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interact!")));
	CanMove = false;
	CanInteract = false;
	EnableInteractBox(true);
	switch (PlayerDirection)
	{
		case EPlayerDirection::Up:
			GetAnimInstance()->PlayAnimationOverride(InteractAnimSequenceUp, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
			break;
		case EPlayerDirection::Down:
			GetAnimInstance()->PlayAnimationOverride(InteractAnimSequenceDown, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
			break;
		case EPlayerDirection::Left:
		case EPlayerDirection::Right:
			GetAnimInstance()->PlayAnimationOverride(InteractAnimSequenceSide, FName("DefaultSlot"), 1.0f, 0.0f, OnInteractOverrideEndDelegate);
			break;
	}
	CurrentPlayerState = EPlayerState::Idle;
}

//������Ϸ
void AMyPaperZDCharacter::PullRod(const FInputActionValue& Value)
{
	if (CurrentPlayerState == EPlayerState::InFishingGame) {
		//��Valueת��Ϊfloat
		float Dir = Value.Get<float>();
		//����ʱ ��zone����, ����ʱ ��zone�½�
		float NewGreenZonePositionY = FishingWidget->GreenZonePositionY;
		if(Dir > 0.0f){
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pull Up!"));
			NewGreenZonePositionY -= FishingWidget->GreenZoneSpeed;
		}
		else if (Dir < 0.0f) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pull Down!"));
			NewGreenZonePositionY += FishingWidget->GreenZoneSpeed;
		}
		FishingWidget->UpdateGreenZonePosition(NewGreenZonePositionY);
	}
}

//����
void AMyPaperZDCharacter::Run(const FInputActionValue& Value)
{
	if (CanMove && !IsTired && !Running)
	{
		Running = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("StartRun!"));
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
	else if (Running)
	{
		Running = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("StopRun!"));
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	}
	else if (IsTired)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player is tired! Cant Run!"));
	}
}

//����
void AMyPaperZDCharacter::Inventory(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Open!"));
	PlayerInventory->PrintInventory();
}

// ������������
void AMyPaperZDCharacter::OnInteractOverrideAnimEnd(bool bCompleted)
{
	CanMove = true;
	if (!IsTired) {
		CanInteract = true;
	}
	EnableInteractBox(false);
}


// ������ʼ�ص�
void AMyPaperZDCharacter::InteractBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	ATreeStump* TreeStump = Cast<ATreeStump>(OtherActor);
	AOres* Ores = Cast<AOres>(OtherActor);
	ACrop* Crop = Cast<ACrop>(OtherActor);
	AAnimalCharacter* Animal = Cast<AAnimalCharacter>(OtherActor);
	AFishSpot* Fish = Cast<AFishSpot>(OtherActor);
	//ACharacter* NPC = Cast<ACharacter>(OtherActor);

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
	else if (Animal) {
		if (CurrentPlayerState == EPlayerState::Interact) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Interact with animal"));
			if (Animal->HadSpawnedProduct) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Animal has already spawned product"));
				return;
			}
			if (!Animal->IsFed) {
				Animal->EatFood();
			}
			else{
				Animal->SpawnProduct();
			}
		}
	}
	else if (Fish) {
		if (CurrentPlayerState == EPlayerState::Fish) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fish!"));
			FishGame();
		}
	}
}



// ������ײ�н����ص�
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
	if (Stamina > 0) {
		if (Stamina > 100) {
			Stamina = 100;
		}
		if (IsTired) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player is not tired anymore!"));
			CanInteract = true;
			IsTired = false;
		}
	}
	else {
		if (Stamina < -150) {
			Stamina = -150;
		}
		if (!IsTired) {
			if (Running) {
				Running = false;
				GetCharacterMovement()->MaxWalkSpeed = 150.0f;
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player is tired!"));
			CanInteract = false;
			IsTired = true;
		}
	}
	PlayerUIWidget->SetStamina(Stamina);
	SDGameInstance->SetPlayerStamina(Stamina);
}

void AMyPaperZDCharacter::UpdateLevel(int ExValue) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gained Exp: %d"), ExValue));
	Exp += ExValue;
	if (Exp >= 10) {
		Exp = 0;
		Level++;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Level Up"));
		PlayerUIWidget->SetLevel(Level);
		SDGameInstance->SetPlayerLevel(1);
		Exp = 0;
	}
}



void AMyPaperZDCharacter::CollectItem(UItem* ItemData) {

	int HealAmount = FMath::RandRange(10, 20);
	int GoldAmount = 1;

	switch (ItemData->ItemType) {
		case CollectableType::Gold:
			SDGameInstance->SetPlayerGold(GoldAmount);
			PlayerUIWidget->SetGold(SDGameInstance->GoldWealth);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Gold"));
			break;
	
		default:
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Default,Pick UP"));
			PlayerInventory->AddItem(ItemData);
			break;
	}
	void AMyPaperZDCharacter::FishGameTick()
	{
		if (FishingWidget) {
			if (FishingWidget->IsInGame && CurrentPlayerState == EPlayerState::InFishingGame) {
				//�ж���Zone�����Ƿ����ཻ,����,������percentage
				float GreenZoneTop = FishingWidget->GreenZonePositionY;
				float GreenZoneBottom = FishingWidget->GreenZonePositionY + FishingWidget->GreenZoneHeight;
				float FishTop = FishingWidget->FishPositionY;
				float FishBottom = FishingWidget->FishPositionY + FishingWidget->FishHeight;
				float FishingSpeed = FishingWidget->PercentageBarSpeed;
				if (GreenZoneBottom < FishTop || GreenZoneTop > FishBottom) {
					FishingSpeed *= -0.4;
				}
				//Percentage
				FishingWidget->SetPercentage(FishingWidget->GamePercentage + FishingSpeed);
				//����ͼƬ
				FishingWidget->UpdateProgressBar();

				//ÿx�������λ��
				FishingWidget->SetFishRandomPosition();

				//�ж��Ƿ�������ʱ�䵽
				if (FishingWidget->GamePercentage >= 100.0f) {
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fish Caught!"));
					FishingWidget->EndFishing();
					//spawn fish

					ActivatePlayer(true);
					CanInteract = true;
					CurrentPlayerState = EPlayerState::Idle;
					UpdateStamina(-5);
				}
			}
		}
	}


}