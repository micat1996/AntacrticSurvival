// Fill out your copyright notice in the Description page of Project Settings.


#include "ModeGame.h"

#include "../Controller/GamePlayerController.h"
#include "../PlayerCharacter/PlayerCharacter.h"


AModeGame::AModeGame()
{
	// 사용될 PlayerControllerClass 를 설정합니다.
	PlayerControllerClass = AGamePlayerController::StaticClass();

	// 사용될 기본 Pawn 을 설정합니다.
	DefaultPawnClass = APlayerCharacter::StaticClass();
}