// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameMode.h"

ACGameMode::ACGameMode()
{
	// 设置默认的Pawn类为自定义的MyPaperZDCharacter
	DefaultPawnClass = AMyPaperZDCharacter::StaticClass();
}