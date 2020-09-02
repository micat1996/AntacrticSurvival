// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "../GameInstance/ASGameInst.h"


void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();

	// ��ư �̺�Ʈ ����
	GameStartBtn->OnReleased.AddDynamic(this, &UTitleWidget::OnStartButtonClicked);
	QuitBtn->OnReleased.AddDynamic(this, &UTitleWidget::OnQuitButtonClicked);
}

void UTitleWidget::FindAllWidget()
{
	GameStartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_GameStart")));
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));
}

void UTitleWidget::OnStartButtonClicked()
{
	UASGameInst* GameInst = Cast<UASGameInst>(GetGameInstance());

	// ���� ���� ���¸� �ʱ�ȭ�մϴ�.
	GameInst->SetGameOver(false);
	
	// ���� ������ �ʱ�ȭ�մϴ�.
	GameInst->InitializeGameScore();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameMap"));
}

void UTitleWidget::OnQuitButtonClicked()
{
	// ������ �����մϴ�.
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false);
}