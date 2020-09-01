// Fill out your copyright notice in the Description page of Project Settings.

#include "ModeTitle.h"
#include "../Controller/TitlePlayerController.h"

AModeTitle::AModeTitle()
{
	// 사용될 PalyerController 의 UClass 를 설정합니다.
	PlayerControllerClass = ATitlePlayerController::StaticClass();

}
