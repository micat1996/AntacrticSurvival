// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ASGameInst.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API UASGameInst : public UGameInstance
{
	GENERATED_BODY()
	
private :
	// 현재 점수
	UPROPERTY()
	float CurrentScore;

	// 게임 오버 상태를 나타냅니다.
	UPROPERTY()
	bool bIsGameOver;

	// 플레이어 캐릭터 객체를 나타냅니다.
	UPROPERTY()
	class APlayerCharacter * PlayerCharacter;

public :
	// 플레이어 캐릭터 객체를 반환합니다.
	class APlayerCharacter* GetPlayerCharacter();

	// 점수를 증가시킵니다.
	void AddScore(float addScore);

	// 현재 점수를 얻습니다.
	FORCEINLINE float GetScore() const
	{ return CurrentScore; }

	// 게임 오버 상태를 설정합니다.
	FORCEINLINE void SetGameOver(bool gameOver)
	{ bIsGameOver = gameOver; }

	// 게임 오버 상태를 얻습니다,.
	FORCEINLINE bool GetGameOver() const
	{ return bIsGameOver; }

};
