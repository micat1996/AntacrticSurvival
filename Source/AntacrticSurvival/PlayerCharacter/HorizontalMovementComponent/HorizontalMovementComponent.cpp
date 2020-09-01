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

	// �÷��̾� ĳ���� ��ü�� ����ϴ�.
	PlayerCharacterInst = Cast<APlayerCharacter>(GetOwner());
}


void UHorizontalMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HorizontalMovement();
}


void UHorizontalMovementComponent::HorizontalMovement()
{
	// PlayerCharacterInstance �� ��ȿ�� ���
	if (IsValid(PlayerCharacterInst))
	{
		// �÷��̾� ĳ���͸� �־��� �������� �̵���ŵ�ϴ�.
		PlayerCharacterInst->AddMovementInput(InputToDirection());
	}
}

FVector UHorizontalMovementComponent::InputToDirection() const
{
	// PlayerCharacterInst �� ��ȿ���� �ʴٸ� (0,0,0) �� ����
	if (!IsValid(PlayerCharacterInst))
		return FVector::ZeroVector;

	return FVector::RightVector * PlayerCharacterInst->
		GetPlayerController()->GetHorizontalInputValue();
}

