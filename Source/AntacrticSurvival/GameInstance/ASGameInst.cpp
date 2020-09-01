#include "ASGameInst.h"
#include "../PlayerCharacter/PlayerCharacter.h"

APlayerCharacter* UASGameInst::GetPlayerCharacter()
{
	if (!IsValid(PlayerCharacter))
	{	
		// 찾은 액터를 저장할 배열
		TArray<AActor*> outActors;

		// 플레이어를 찾습니다.
		UGameplayStatics::GetAllActorsOfClass(
			GetWorld(),
			APlayerCharacter::StaticClass(),
			outActors);
		/// - GetAllActorsOfClass() : 특정한 형태의 액터를 찾습니다.
		/// - 해당 작업은 빠른 작업이 아니므로 항상 필요한 
		///   경우에만 사용해야 합니다.

		if (outActors.Num() == 0) return nullptr;

		// 찾은 액터를 APlayerCharacter 형태로 캐스팅합니다.
		PlayerCharacter = Cast<APlayerCharacter>(outActors[0]);
	}

	return PlayerCharacter;
}

void UASGameInst::AddScore(float addScore)
{
	if (!bIsGameOver)
	{
		// 점수를 증가시킵니다.
		CurrentScore += addScore;

		// 점수가 음수가 될수 없도록 합니다.
		if (CurrentScore < 0.0f)
			CurrentScore = 0.0f;
	}
}
