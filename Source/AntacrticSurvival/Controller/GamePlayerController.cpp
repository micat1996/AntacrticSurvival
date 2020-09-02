#include "GamePlayerController.h"
#include "../Widget/GameWidget.h"
#include "../GameInstance/ASGameInst.h"


AGamePlayerController::AGamePlayerController(
	const FObjectInitializer& ObjectInitializer)
{
	LoadAsset();
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UASGameInst>(GetGameInstance());

	SetCameraView();

	CreateWdigetInScreen();
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(
		TEXT("Horizontal"), this, &AGamePlayerController::HorizontalInput);
	/// - BindAxis : ������Ʈ �������� ���ǵ� ��� ���� �޼��带 ����մϴ�.
	/// - ��ϵ� �� �ִ� ���� : void (float)
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameInst->AddScore(DeltaTime);
}

void AGamePlayerController::CreateWdigetInScreen()
{
	CreateWidget<UGameWidget>(this, GameWidgetClass)->AddToViewport();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AGamePlayerController::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UGameWidget> WIDGETBP_GAMEWIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WidgetBP_Game.WidgetBP_Game_C'"));

	if (WIDGETBP_GAMEWIDGET.Succeeded())
		GameWidgetClass = WIDGETBP_GAMEWIDGET.Class;
}

void AGamePlayerController::SetCameraView()
{
	TArray<AActor*> findActors;
	/// - �𸮾� �������� �����ϴ� �����̳�
	/// - TArray : �������� ũ�⸦ ������ �� �ִ� �迭
	/// - TSet : ���� ������ �����Ǹ�, �ߺ� ������� �ʽ��ϴ�.
	/// - TMap : Ű�� ���� �Բ� ����Ǹ�, Ű�� �ߺ� ������� �ʽ��ϴ�.


	// "GameCamera" �� ��ġ�ϴ� Tag �� ���� ���͸� ã���ϴ�.
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), TEXT("GameCamera"), findActors);
	/// - UGameplayStatics : ��ƿ�� ���� �޼��带 �����ϴ� Ŭ�����Դϴ�.
	/// - GetAllActorsWithTag(WorldContextObejct, Tag, OutActors)
	///   Tag �� ��ġ�ϴ� ���͸� WorldContextObejct �� ������ ���忡�� ã�� 
	///   OutActors �� �����մϴ�.
	/// - WorldContextObejct : ã�� ���Ͱ� �����ϴ� ���� �ν��Ͻ��� �ǹ��մϴ�.
	/// - Tag : ã���� �ϴ� ���Ͱ� ������ Tag �� �ǹ��մϴ�.
	/// - OutActors : ã�� ���͸� ������ TArray<AActors*> �� �����մϴ�.

	// ã�� ���Ͱ� �����Ѵٸ�
	if (findActors.Num() > 0)
	{
		/// TArray.Num() : ����� ������ ��ȯ�մϴ�.

		// ī�޶� �並 "GameCamera" �� ���� Tag �� ���� ���ͷ� �����մϴ�.
		SetViewTargetWithBlend(findActors[0]);
		/// - SetViewTargetWithBlend(NewViewTarget)
		/// - �� Ÿ���� NewViewTarget ���� �����մϴ�.
	}




}


void AGamePlayerController::HorizontalInput(float axis)
{
	// �Է� ���� �̿��Ͽ� ��Ʈ�ѷ��� ȸ����ŵ�ϴ�.
	SetControlRotation(
		FRotator(0.0f, ((HorizontalInputValue = axis) * -90.0f) + 180.0f, 0.0f));

//	UE_LOG(LogTemp, Warning, TEXT("HorizontalInputValue = %.2f"), 
//		HorizontalInputValue);
	/// - UE_LOG(ī�װ�, �α� ����, ����, args)
	/// - ī�װ� : �α��� ī�װ��� �����մϴ�.
	/// - �α� ���� : �α��� ������ ��Ÿ���ϴ�.
	///   - Fatal : �α� ���ϰ� �ֿܼ� �׻� ��µǸ� ���α׷��� ����˴ϴ�.
	///   - Error : �������� �ְܼ� ���Ͽ� ��µ˴ϴ�.
	///   - Warning : Ȳ������ �ְܼ� ���Ͽ� ��µ˴ϴ�.
	///   - Display : �ְܼ� ���Ͽ� ��µ˴ϴ�.
	///   - Log : ���Ͽ� ��µ˴ϴ�. �����Ϳ��� ������ ���� �ֿܼ��� ��µ˴ϴ�.
	///   - Verbose : �α� ���Ͽ��� ��µ˴ϴ�.
	///   - VeryVerbose : �α� ���Ͽ��� ��µǸ� �ſ� ���� �޽����� ��µ˴ϴ�.


}