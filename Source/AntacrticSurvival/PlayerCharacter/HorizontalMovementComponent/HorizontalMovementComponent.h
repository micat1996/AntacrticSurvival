// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "Components/ActorComponent.h"
#include "HorizontalMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANTACRTICSURVIVAL_API UHorizontalMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	class APlayerCharacter* PlayerCharacterInst;

public:	
	UHorizontalMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// 수평 이동
	void HorizontalMovement();

	// 좌우 입력값을 플레이어 캐릭터가 사용할 수 있는 방향으로 변환하여 반환하는 메서드
	FVector InputToDirection() const;
		
};
