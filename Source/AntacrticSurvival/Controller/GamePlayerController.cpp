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
	/// - BindAxis : 프로젝트 설정에서 정의된 축과 사용될 메서드를 등록합니다.
	/// - 등록될 수 있는 형태 : void (float)
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
	/// - 언리얼 엔진에서 제공하는 컨테이너
	/// - TArray : 동적으로 크기를 조절할 수 있는 배열
	/// - TSet : 저장 순서가 유지되며, 중복 저장되지 않습니다.
	/// - TMap : 키와 값이 함꼐 저장되며, 키는 중복 저장되지 않습니다.


	// "GameCamera" 와 일치하는 Tag 를 가진 액터를 찾습니다.
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), TEXT("GameCamera"), findActors);
	/// - UGameplayStatics : 유틸성 정적 메서드를 제공하는 클래스입니다.
	/// - GetAllActorsWithTag(WorldContextObejct, Tag, OutActors)
	///   Tag 와 일치하는 액터를 WorldContextObejct 에 전달한 월드에서 찾아 
	///   OutActors 에 저장합니다.
	/// - WorldContextObejct : 찾을 액터가 존재하는 월드 인스턴스를 의미합니다.
	/// - Tag : 찾고자 하는 액터가 가지는 Tag 를 의미합니다.
	/// - OutActors : 찾은 액터를 저장할 TArray<AActors*> 를 전달합니다.

	// 찾은 액터가 존재한다면
	if (findActors.Num() > 0)
	{
		/// TArray.Num() : 요소의 개수를 반환합니다.

		// 카메라 뷰를 "GameCamera" 와 같은 Tag 를 갖는 액터로 설정합니다.
		SetViewTargetWithBlend(findActors[0]);
		/// - SetViewTargetWithBlend(NewViewTarget)
		/// - 뷰 타깃을 NewViewTarget 으로 설정합니다.
	}




}


void AGamePlayerController::HorizontalInput(float axis)
{
	// 입력 값을 이용하여 컨트롤러를 회전시킵니다.
	SetControlRotation(
		FRotator(0.0f, ((HorizontalInputValue = axis) * -90.0f) + 180.0f, 0.0f));

//	UE_LOG(LogTemp, Warning, TEXT("HorizontalInputValue = %.2f"), 
//		HorizontalInputValue);
	/// - UE_LOG(카테고리, 로그 레벨, 내용, args)
	/// - 카테고리 : 로그의 카테고리를 설정합니다.
	/// - 로그 레벨 : 로그의 수준을 나타냅니다.
	///   - Fatal : 로그 파일과 콘솔에 항상 출력되며 프로그램이 종료됩니다.
	///   - Error : 적색으로 콘솔과 파일에 출력됩니다.
	///   - Warning : 황색으로 콘솔과 파일에 출력됩니다.
	///   - Display : 콘솔과 파일에 출력됩니다.
	///   - Log : 파일에 출력됩니다. 에디터에서 실행할 때는 콘솔에도 출력됩니다.
	///   - Verbose : 로그 파일에만 출력됩니다.
	///   - VeryVerbose : 로그 파일에만 출력되며 매우 상세한 메시지가 출력됩니다.


}