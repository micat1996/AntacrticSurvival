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
	// ���� ����
	UPROPERTY()
	float CurrentScore;

	// ���� ���� ���¸� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bIsGameOver;

	// �÷��̾� ĳ���� ��ü�� ��Ÿ���ϴ�.
	UPROPERTY()
	class APlayerCharacter * PlayerCharacter;

public :
	// �÷��̾� ĳ���� ��ü�� ��ȯ�մϴ�.
	class APlayerCharacter* GetPlayerCharacter();

	// ������ ������ŵ�ϴ�.
	void AddScore(float addScore);

	// ���� ������ ����ϴ�.
	FORCEINLINE float GetScore() const
	{ return CurrentScore; }

	// ���� ���� ���¸� �����մϴ�.
	FORCEINLINE void SetGameOver(bool gameOver)
	{ bIsGameOver = gameOver; }

	// ���� ���� ���¸� ����ϴ�,.
	FORCEINLINE bool GetGameOver() const
	{ return bIsGameOver; }

};
