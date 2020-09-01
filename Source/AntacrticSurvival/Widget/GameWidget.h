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

	// ���� �ؽ�Ʈ ������ ��Ÿ�� ����
	class UTextBlock* ScoreText;

	// ����� ���¸� ��Ÿ���� ��� �̹���
	class UImage* HungryImage;

	// ���� ���� ĵ����
	class UCanvasPanel* GameOverCanvas;



public :
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private :
	// C++ ���� �ٷ� �������� ã���ϴ�.
	void FindAllWidet();

	// TextBlock �� ���ε��� �޼����Դϴ�.
	/// - ������ �����մϴ�.
	UFUNCTION()
	FText UpdateScore();

	// ����� ���¸� ��Ÿ���� �̹����� �¿�� �̵���ŵ�ϴ�.
	void MoveHungryImage();

	void GameOver();

};
