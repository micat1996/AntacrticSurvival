// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/TitleWidget.h"
#include "TitlePlayerController.h"

ATitlePlayerController::ATitlePlayerController(
	const FObjectInitializer& ObjectInityializer) :
	APlayerController(ObjectInityializer)
{
	LoadAsset();
}

void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	CreateWidgetInScreen();
	SetCameraView();
}

void ATitlePlayerController::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> WIDGETBP_TITLEWIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WidgetBP_Title.WidgetBP_Title_C'"));

	if (WIDGETBP_TITLEWIDGET.Succeeded())
		TitleWidgetClass = WIDGETBP_TITLEWIDGET.Class;
}

void ATitlePlayerController::SetCameraView()
{
	TArray<AActor*> findActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("GameCamera"), findActors);
	SetViewTargetWithBlend(findActors[0]);
}

void ATitlePlayerController::CreateWidgetInScreen()
{
	TitleWidget = CreateWidget<UTitleWidget>(this, TitleWidgetClass);
	TitleWidget->AddToViewport();

	// �Է� ��带 UI ���� ����
	SetInputMode(FInputModeUIOnly());

	// ���콺�� ǥ���մϴ�.
	bShowMouseCursor = true;
}