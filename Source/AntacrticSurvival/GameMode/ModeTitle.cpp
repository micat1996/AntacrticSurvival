// Fill out your copyright notice in the Description page of Project Settings.

#include "ModeTitle.h"
#include "../Controller/TitlePlayerController.h"

AModeTitle::AModeTitle()
{
	// ���� PalyerController �� UClass �� �����մϴ�.
	PlayerControllerClass = ATitlePlayerController::StaticClass();

}
