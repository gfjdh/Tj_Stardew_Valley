// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameMode.h"

ACGameMode::ACGameMode()
{
	// ����Ĭ�ϵ�Pawn��Ϊ�Զ����MyPaperZDCharacter
	DefaultPawnClass = AMyPaperZDCharacter::StaticClass();
}