// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingMovementComponent.h"

// Sets default values for this component's properties
UFloatingMovementComponent::UFloatingMovementComponent()
{
	// �ش� ������Ʈ���� Tick �޼��� ȣ���� ����ϵ��� �� �������� �����մϴ�.
	PrimaryComponentTick.bCanEverTick = true;

	FloatingSpeed = 200.0f;
	FloatingValue = 40.0f;
	StartTime = FMath::FRandRange(0.0f, 1.0f);
	//StartTime = FMath::RandRange(0.0f, 1.0f);
	/// - FRandRange(float min, flaot max) : min �� max ������ ������ ��ȯ�մϴ�.
}


// Called when the game starts
void UFloatingMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// - Super : ���� Ŭ������ ��Ÿ���ϴ�.

	ActorBeginLocation = GetOwner()->GetActorLocation();
	/// - GetOwner() : �ش� ������Ʈ�� �����ϴ� ���͸� ��ȯ�մϴ�.
	/// - ActorInstance->GetActorLocation() : ������ ��ġ�� FVector ������ �����ͷ� ��ȯ
}

// Called every frame
void UFloatingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FloatingMovement(DeltaTime);
}

void UFloatingMovementComponent::FloatingMovement(float DeltaTime)
{
	// ���� ������ ��ġ�� �����մϴ�.
	FVector newFloatingLocation = ActorBeginLocation;

	// ���� Z ��ǥ�� �����մϴ�.
	newFloatingLocation.Z = ActorBeginLocation.Z + FMath::Sin(
		(GetWorld()->TimeSeconds + StartTime) * FloatingSpeed * DeltaTime) * FloatingValue;
	/// - FMath : ���а� ���õ� ���� �Լ����� �����ϴ� ����ü
	/// - TimeSeconds : ������ ���۵� �� ��ŭ�� �ð��� ���������� ��Ÿ���ϴ�.

	GetOwner()->SetActorLocation(newFloatingLocation);
	/// - SetActorLocation() ������ ��ġ�� �����մϴ�.

}