// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API UPlayerCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()


protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HorizontalSpeed;
	/// - BlueprintReadOnly : �������Ʈ Ŭ�������� �б� �������� ������ ��Ÿ���ϴ�.
	/// - BlueprintReadWrite : �������Ʈ Ŭ�������� �а� ���Ⱑ ���������ϴ�.

private :
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		

	
};
