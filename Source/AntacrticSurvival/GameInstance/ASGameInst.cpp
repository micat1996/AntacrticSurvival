#include "ASGameInst.h"
#include "../PlayerCharacter/PlayerCharacter.h"

APlayerCharacter* UASGameInst::GetPlayerCharacter()
{
	if (!IsValid(PlayerCharacter))
	{	
		// ã�� ���͸� ������ �迭
		TArray<AActor*> outActors;

		// �÷��̾ ã���ϴ�.
		UGameplayStatics::GetAllActorsOfClass(
			GetWorld(),
			APlayerCharacter::StaticClass(),
			outActors);
		/// - GetAllActorsOfClass() : Ư���� ������ ���͸� ã���ϴ�.
		/// - �ش� �۾��� ���� �۾��� �ƴϹǷ� �׻� �ʿ��� 
		///   ��쿡�� ����ؾ� �մϴ�.

		if (outActors.Num() == 0) return nullptr;

		// ã�� ���͸� APlayerCharacter ���·� ĳ�����մϴ�.
		PlayerCharacter = Cast<APlayerCharacter>(outActors[0]);
	}

	return PlayerCharacter;
}

void UASGameInst::AddScore(float addScore)
{
	if (!bIsGameOver)
	{
		// ������ ������ŵ�ϴ�.
		CurrentScore += addScore;

		// ������ ������ �ɼ� ������ �մϴ�.
		if (CurrentScore < 0.0f)
			CurrentScore = 0.0f;
	}
}
