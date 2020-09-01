// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeGame.h"

#include "../Controller/GamePlayerController.h"
#include "../PlayerCharacter/PlayerCharacter.h"


AModeGame::AModeGame()
{
	// ���� PlayerControllerClass �� �����մϴ�.
	PlayerControllerClass = AGamePlayerController::StaticClass();

	// ���� �⺻ Pawn �� �����մϴ�.
	DefaultPawnClass = APlayerCharacter::StaticClass();
}