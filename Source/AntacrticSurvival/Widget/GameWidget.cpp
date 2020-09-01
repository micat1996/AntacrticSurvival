#include "GameWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "../PlayerCharacter/PlayerCharacter.h"
#include "../GameInstance/ASGameInst.h"


void UGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidet();

	GameInst = Cast<UASGameInst>(GetGameInstance());

	// ScoreText 의 값이 UpdateScore() 메서드의 반환 값으로 
	// 계속 업데이트 되도록 합니다.
	ScoreText->TextDelegate.BindDynamic(this, &UGameWidget::UpdateScore);

}

void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	MoveHungryImage();
	GameOver();
}

void UGameWidget::FindAllWidet()
{
	ScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScoreText")));
	/// - GetWidgetFromName(name) : name 과 일치하는 widget 을 찾아
	///   UWidget* 형식으로 리턴합니다.

	HungryImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_Current")));

	GameOverCanvas = Cast<UCanvasPanel>(
		GetWidgetFromName(TEXT("CanvasPanel_GameOver")));
}

FText UGameWidget::UpdateScore()
{
	FString scoreStr = FString::Printf(TEXT("%.2f"), GameInst->GetScore());
	/// - FString::Printf() : 지정한 형식으로 변환하여 문자열로 반환합니다.

	FString returnString = FString(TEXT("현재 점수\n")).Append(scoreStr);

	return FText::FromString(returnString);
}

void UGameWidget::MoveHungryImage()
{
	APlayerCharacter* playerCharacter = GameInst->GetPlayerCharacter();

	if (!IsValid(playerCharacter)) return;

	// Render Transform 을 얻습니다.
	FWidgetTransform hungryImageTransform = HungryImage->RenderTransform;
	hungryImageTransform.Translation.X = playerCharacter->GetHungryValue() * 10.0f;

	// 변경한 Render Transform 을 설정합니다.
	HungryImage->SetRenderTransform(hungryImageTransform);

}

void UGameWidget::GameOver()
{
	// 게임 오버 상태이며, 캔버스가 보여지지 않는 상태라면
	if (GameInst->GetGameOver() && !GameOverCanvas->IsVisible())
	{
		// 보이는 상태로 변경합니다.
		GameOverCanvas->SetVisibility(ESlateVisibility::Visible);
	}
}