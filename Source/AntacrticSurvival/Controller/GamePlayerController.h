// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API AGamePlayerController : 
	public APlayerController
{
	GENERATED_BODY()


private :
	float HorizontalInputValue;

	class UASGameInst* GameInst;

	UPROPERTY()
	TSubclassOf<class UGameWidget> GameWidgetClass;




public :
	AGamePlayerController(const FObjectInitializer& ObjectInitializer = 
		FObjectInitializer::Get());

protected :
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public :
	virtual void Tick(float DeltaTime) override;


private :
	void LoadAsset();

	// GameWidget 을 화면에 생성합니다.
	void CreateWdigetInScreen();

	// 카메라 뷰를 설정합니다.
	void SetCameraView();

	void HorizontalInput(float axis);



public :
	FORCEINLINE float GetHorizontalInputValue() const
	{ return HorizontalInputValue; }
};
