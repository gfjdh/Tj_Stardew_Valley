#include "TreeStump.h"
#include "MyPaperZDCharacter.h"

ATreeStump::ATreeStump()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	TreeSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	TreeSprite->SetupAttachment(RootComponent);

}

void ATreeStump::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ATreeStump::OverlapBegin);
	
}

void ATreeStump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreeStump::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Can be chopped"));
	}

}

void ATreeStump::Chop(AActor* OtherActor) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		//�ж��Ƿ���
		Health--;
		if (Health != 0)
			return;
		int DropNumber = FMath::RandRange(MinDropNumber, MaxDropNumber);
		while (DropNumber--) {
			//Զ��������5-30��λ��
			FVector Location = GetActorLocation();
			FVector PlayerLocation = OtherActor->GetActorLocation();
			FVector Direction = Location - PlayerLocation;
			Direction.Normalize();
			Location += Direction * FMath::RandRange(5, 30);
			ACollectableEntity* Product = GetWorld()->SpawnActor<ACollectableEntity>(ProductClass, Location, FRotator::ZeroRotator);
		}
		//�����Լ�
		Destroy();
	}
}