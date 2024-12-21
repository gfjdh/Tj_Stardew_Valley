// Fill out your copyright notice in the Description page of Project Settings.


#include "Crop.h"
#include "MyPaperZDCharacter.h"
#include <random>
#include <time.h>

// Sets default values
ACrop::ACrop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	TreeSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TreeSprite"));
	TreeSprite->SetupAttachment(RootComponent);

	DefectedSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DefectedSprite"));
	DefectedSprite -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrop::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACrop::OverlapBegin);
}

// Called every frame
void ACrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JudgeMaturity();
	SwitchSprite();
}

void ACrop::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AFarmLand* FarmLand = Cast<AFarmLand>(OtherActor);
	ACrop* Crop = Cast<ACrop>(OtherActor);
	if (FarmLand) {
		if (FarmLand->WaterStage == 0) {
			IsWet = 0;
		}
		else {
			IsWet = 1;
		}
	}
}

//ͬ���ģ�����Ҳ����д��������߼������������Ʒ�ȵ�

//�ı䵱ǰ����״̬�ĺ���
void ACrop::JudgeMaturity()
{
	srand(time(0));
	if (Maturity < 1000) {
		//����������ٶ���һ����Χ�����
		Maturity += (double)(rand() % 5 / 10 + 0.5)*IsWet;
	}

	if (Maturity < 200) {
		status = 0;
	}
	else if (Maturity >= 200&&Maturity<500) {
		status = 1;
	}
	else if(Maturity>=500 && Maturity<1000){
		status = 2;
	}
	else {
		status = 3;
	}

	GetDefect();
}

//�ı䵱ǰ�������
void ACrop::SwitchSprite()
{
	switch (status) {
	case 0:
		this->TreeSprite->SetSprite(CropStageSprite1);
		break;
	case 1:
		this->TreeSprite->SetSprite(CropStageSprite2);
		break;
	case 2:
		this->TreeSprite->SetSprite(CropStageSprite3);
		break;
	case 3:
		this->TreeSprite->SetSprite(CropStageSprite4);
		break;
	}
}

//���ɲ�Ʒ
void ACrop::SpawnProducts()
{
	FVector CropLocation = this->GetActorLocation();
	srand(time(0));
	int OffsetX = (rand() - RAND_MAX) % 20;
	int OffsetY = (rand() - RAND_MAX) % 19;
	FVector ProductsSpawnLocation = CropLocation + FVector(OffsetX, OffsetY, 0);
	//����׶��ջ񣬿������ɲ�Ʒ
	if (status == 3){
		GetWorld()->SpawnActor<ACollectableEntity>(ProductActor1, ProductsSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
	}

	//��������,����status�����������������
	for (int i = 1; i < status+2; i++) {
		srand(time(0) + i * 100);
		OffsetX = (rand() - RAND_MAX) % 20;
		OffsetY = (rand() - RAND_MAX) % 19;
		ProductsSpawnLocation = CropLocation + FVector(OffsetX, OffsetY, 0);
		GetWorld()->SpawnActor<ACollectableEntity>(ProductActor2, ProductsSpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
	}

}


void ACrop::GetDefect() {
	if (!IsDefected) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Crop has not been defected!"));
		int RandomValue = FMath::RandRange(0, 100);
		if (RandomValue <= DefectRate)
		{
			IsDefected = true;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crop has been defected!"));

		}
	}
}