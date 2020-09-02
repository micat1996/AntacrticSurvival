// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "../GameInstance/ASGameInst.h"


void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();

	// 버튼 이벤트 설정
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

	// 게임 오버 상태를 초기화합니다.
	GameInst->SetGameOver(false);
	
	// 게임 점수를 초기화합니다.
	GameInst->InitializeGameScore();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameMap"));
}

void UTitleWidget::OnQuitButtonClicked()
{
	// 게임을 종료합니다.
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false);
}