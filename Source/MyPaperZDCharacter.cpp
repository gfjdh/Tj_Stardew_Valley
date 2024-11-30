// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperZDCharacter.h"

AMyPaperZDCharacter::AMyPaperZDCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// ����Ͷ��ģʽΪ����
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	// �����������Ϊ512
	Camera->OrthoWidth = 512.0f;

	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
	PlayerSprite->SetupAttachment(RootComponent);

}
