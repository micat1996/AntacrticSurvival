// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "GameFramework/PlayerController.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API ATitlePlayerController : public APlayerController
{
	GENERATED_BODY()

private :
	class UTitleWidget* TitleWidget;
	TSubclassOf<class UTitleWidget> TitleWidgetClass;

public :
	ATitlePlayerController(
		const FObjectInitializer& ObjectInityializer = FObjectInitializer::Get());

protected :
	virtual void BeginPlay() override;

	void LoadAsset();
	void SetCameraView();
	void CreateWidgetInScreen();
};
