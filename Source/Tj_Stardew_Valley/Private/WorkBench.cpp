// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkBench.h"
#include "MyPaperZDCharacter.h"



void AWorkBench::OpenCookMenu(AActor* OtherActor) {
	AMyPaperZDCharacter* Player = Cast<AMyPaperZDCharacter>(OtherActor);
	if (Player) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Open Craft Menu"));
		Player->CraftWidget->DisplayWidget(true);
	}
}