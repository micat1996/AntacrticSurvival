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
	/// - BlueprintReadOnly : 블루프린트 클래스에서 읽기 전용으로 사용됨을 나타냅니다.
	/// - BlueprintReadWrite : 블루프린트 클래스에서 읽고 쓰기가 가능해집니다.

private :
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		

	
};
