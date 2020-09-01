// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalMovementComponent.h"
#include "../PlayerCharacter.h"
#include "../../Controller/GamePlayerController.h"

UHorizontalMovementComponent::UHorizontalMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHorizontalMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 캐릭터 객체를 얻습니다.
	PlayerCharacterInst = Cast<APlayerCharacter>(GetOwner());
}


void UHorizontalMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HorizontalMovement();
}


void UHorizontalMovementComponent::HorizontalMovement()
{
	// PlayerCharacterInstance 가 유효할 경우
	if (IsValid(PlayerCharacterInst))
	{
		// 플레이어 캐릭터를 주어진 방향으로 이동시킵니다.
		PlayerCharacterInst->AddMovementInput(InputToDirection());
	}
}

FVector UHorizontalMovementComponent::InputToDirection() const
{
	// PlayerCharacterInst 가 유효하지 않다면 (0,0,0) 을 리턴
	if (!IsValid(PlayerCharacterInst))
		return FVector::ZeroVector;

	return FVector::RightVector * PlayerCharacterInst->
		GetPlayerController()->GetHorizontalInputValue();
}

