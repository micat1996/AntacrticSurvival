// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

private :
	class UButton* GameStartBtn;
	class UButton* QuitBtn;


public :
	virtual void NativeOnInitialized() override;
	
private :
	void FindAllWidget();

	// GameStart ��ư�� ������ ��� ȣ���� �޼���
	UFUNCTION()
	void OnStartButtonClicked();

	// Quit ��ư�� ������ ��� ȣ���� �޼���
	UFUNCTION()
	void OnQuitButtonClicked();

	
};
