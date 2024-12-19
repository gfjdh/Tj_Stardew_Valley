#include "NPC.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "MyPaperZDCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = true;
	// ����һ�����������Ϊ�����
    NPCCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("NPCCapsuleComponent"));
    SetRootComponent(NPCCapsuleComponent);

    // ������ײ����
	NPCCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);// ������ײ����Ϊ��ѯ������
	NPCCapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);// ������ײ��������ΪPawn
	NPCCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);// ������ײ��ӦΪ����
	// ����һ��Flipbook�����ΪNPC���Ӿ����
    NPCFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NPCFlipbookComponent"));
    NPCFlipbookComponent->SetupAttachment(NPCCapsuleComponent);
	// ����һ���ı����������ʾ�Ի�
    DialogueWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DialogueWidgetComponent"));
	DialogueWidgetComponent->SetupAttachment(NPCCapsuleComponent);// ���öԻ�����ĸ����Ϊ�������
	DialogueWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);// ���öԻ�����Ŀռ�Ϊ��Ļ�ռ�
	DialogueWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));// ���öԻ�����Ĵ�С
	DialogueWidgetComponent->SetVisibility(false);// ���öԻ�������ɼ�
	DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));// ���öԻ������λ��

    // �����Զ���Widget��
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/BluePrints/NPC/DialogueWidget"));// ���öԻ������Widget��
	if (WidgetClass.Succeeded())// ����ҵ���Widget��
    {
		DialogueWidgetComponent->SetWidgetClass(WidgetClass.Class);// ���öԻ������Widget��
    }

	// ����NPC���ƶ�����
    MovementAreaCenter = FVector(-150.0f, -150.0f, 0.0f); // ����NPC���ƶ���������
    MovementAreaRadius = 100.0f; // ����NPC���ƶ�����뾶
    MovementSpeed = 10.0f; // ����NPC���ƶ��ٶ�
    CurrentDirection = FVector::ZeroVector; // ��ʼ��NPC�ķ���
    TimeToChangeDirection = 0.0f; // ��ʼ��ʱ��

    // ��ʼ������ָ��
    IdleRightAnimation = nullptr;
    IdleLeftAnimation = nullptr;
    IdleUpAnimation = nullptr;
    IdleDownAnimation = nullptr;
    MoveRightAnimation = nullptr;
    MoveLeftAnimation = nullptr;
    MoveUpAnimation = nullptr;
    MoveDownAnimation = nullptr;

    // ��ʼ�������������
    RandomStream.Initialize(FDateTime::Now().GetMillisecond());

	DialogueLines = { TEXT("Hello!"), TEXT("How are you?"), TEXT("Nice weather today!") };
    // ��ʼ���Ի��ɼ���״̬
    bIsDialogueVisible = false;
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveRandomly(DeltaTime);
    ANPC::UpdateAnimation();

    // �������Ƿ񿿽��������Ի�
    CheckForPlayerInteractionBox();
}

// ���ѡ��һ���Ի��ַ�������ʾ
void ANPC::DisplayRandomDialogue()
{
    if (DialogueLines.Num() > 0)
    {
        int32 RandomIndex = RandomStream.RandRange(0, DialogueLines.Num() - 1);
        FString RandomDialogue = DialogueLines[RandomIndex];

		// ��ȡ�Ի��������UserWidget����
        UUserWidget *DialogueWidget = DialogueWidgetComponent->GetUserWidgetObject();
        if (DialogueWidget)
        {
            UTextBlock *DialogueText = Cast<UTextBlock>(DialogueWidget->GetWidgetFromName(TEXT("DialogueText")));
            if (DialogueText)
            {
				DialogueText->SetText(FText::FromString(RandomDialogue));// ���öԻ��ı�
            }
        }

        DialogueWidgetComponent->SetVisibility(true);
        bIsDialogueVisible = true;

        // ȷ���Ի��������λ����NPC��ͷ��
        FVector NPCPosition = GetActorLocation();
        DialogueWidgetComponent->SetRelativeLocation(FVector(0.0f, 5.0f, 15.0f));
    }
}

// �������Ƿ񿿽��������Ի�
void ANPC::CheckForPlayerInteractionBox()
{
    static float DialogueCooldown = 0.0f;

    if (DialogueCooldown > 0.0f)
    {
        DialogueCooldown -= GetWorld()->GetDeltaSeconds();
        return;
    }

    TArray<AActor *> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AMyPaperZDCharacter::StaticClass());

    bool bPlayerNearby = false;

    for (AActor *Actor : OverlappingActors)
    {
        AMyPaperZDCharacter *Player = Cast<AMyPaperZDCharacter>(Actor);
        if (Player)
        {
            // ��ȡ��ҵĻ�����ײ��
            UBoxComponent *InteractionBox = nullptr;
            switch (Player->PlayerDirection)
            {
                case EPlayerDirection::Up:
                    InteractionBox = Player->InteractionBoxUp;
                    break;
                case EPlayerDirection::Down:
                    InteractionBox = Player->InteractionBoxDown;
                    break;
                case EPlayerDirection::Left:
                    InteractionBox = Player->InteractionBoxLeft;
                    break;
                case EPlayerDirection::Right:
                    InteractionBox = Player->InteractionBoxRight;
                    break;
            }

            if (InteractionBox && InteractionBox->IsOverlappingActor(this))
            {
                DisplayRandomDialogue();
                CurrentDirection = FVector::ZeroVector;
                bPlayerNearby = true;
                DialogueCooldown = 3.0f; // ������ȴʱ��Ϊ5��
                break;
            }
        }
    }

    if (!bPlayerNearby && bIsDialogueVisible)
    {
        DialogueWidgetComponent->SetVisibility(false);
        bIsDialogueVisible = false;
    }
}


//MoveRandomly()����������NPC��ָ��������������ƶ���
void ANPC::MoveRandomly(float DeltaTime)
{
    // ����NPC�ķ���
    if (TimeToChangeDirection <= 0.0f)
    {
        // ����һ����������ϡ��¡����ң�
        int32 Direction = RandomStream.RandRange(0, 4);
        switch (Direction)
        {
            case 4:
				CurrentDirection = FVector(0.0f, 0.0f, 0.0f); // ֹͣ
                break;
            case 3:
                CurrentDirection = FVector(1.0f, 0.0f, 0.0f); // ��
                break;
            case 2:
                CurrentDirection = FVector(-1.0f, 0.0f, 0.0f); // ��
                break;
            case 1:
                CurrentDirection = FVector(0.0f, -1.0f, 0.0f); // ��
                break;
            case 0:
                CurrentDirection = FVector(0.0f, 1.0f, 0.0f); // ��
                break;
        }
        // ����һ�����ʱ�����ı䷽��
        TimeToChangeDirection = RandomStream.RandRange(1.0f, 3.0f);
    }

    // �ƶ�NPC
    FVector NewLocation = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

    // ȷ��NPC�����Ƴ�ָ��������
    if (FVector::Dist(NewLocation, MovementAreaCenter) > MovementAreaRadius)
    {
        NewLocation = MovementAreaCenter + (NewLocation - MovementAreaCenter).GetSafeNormal() * MovementAreaRadius;
        CurrentDirection = -CurrentDirection; // ��ת����
    }

    SetActorLocation(NewLocation);

    // ����ʱ��
    TimeToChangeDirection -= DeltaTime;
}

//UpdateAnimation()�������ڸ���NPC�ķ���������NPC�Ķ�����
void ANPC::UpdateAnimation()
{
    if (CurrentDirection.IsNearlyZero())
    {
        // Idle animations
        if (FMath::Abs(CurrentDirection.X) > FMath::Abs(CurrentDirection.Y))
        {
            if (CurrentDirection.X > 0)
            {
                NPCFlipbookComponent->SetFlipbook(IdleRightAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(IdleLeftAnimation);
            }
        }
        else
        {
            if (CurrentDirection.Y > 0)
            {
                NPCFlipbookComponent->SetFlipbook(IdleUpAnimation);
            }
            else
            {
                NPCFlipbookComponent->SetFlipbook(IdleDownAnimation);
            }
        }
    }
    else
    {
        if (CurrentDirection.Y == 0 && CurrentDirection.X > 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveRightAnimation);
        }
        else if (CurrentDirection.Y == 0 && CurrentDirection.X < 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveLeftAnimation);
        }
        else if (CurrentDirection.X == 0 && CurrentDirection.Y < 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveUpAnimation);
        }
        else if (CurrentDirection.X == 0 && CurrentDirection.Y > 0)
        {
            NPCFlipbookComponent->SetFlipbook(MoveDownAnimation);
        }
    }
}
