// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UASGameInst* GameInst;

	// 점수 텍스트 위젯을 나타낼 변수
	class UTextBlock* ScoreText;

	// 배고픔 상태를 나타내는 펭귄 이미지
	class UImage* HungryImage;

	// 게임 오버 캔버스
	class UCanvasPanel* GameOverCanvas;



public :
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private :
	// C++ 에서 다룰 위젯들을 찾습니다.
	void FindAllWidet();

	// TextBlock 에 바인딩할 메서드입니다.
	/// - 점수를 변경합니다.
	UFUNCTION()
	FText UpdateScore();

	// 배고픔 상태를 나타내는 이미지를 좌우로 이동시킵니다.
	void MoveHungryImage();

	void GameOver();

};
