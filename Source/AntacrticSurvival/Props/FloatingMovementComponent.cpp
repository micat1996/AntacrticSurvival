// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingMovementComponent.h"

// Sets default values for this component's properties
UFloatingMovementComponent::UFloatingMovementComponent()
{
	// 해당 컴포넌트에서 Tick 메서드 호출을 사용하도록 할 것인지를 결정합니다.
	PrimaryComponentTick.bCanEverTick = true;

	FloatingSpeed = 200.0f;
	FloatingValue = 40.0f;
	StartTime = FMath::FRandRange(0.0f, 1.0f);
	//StartTime = FMath::RandRange(0.0f, 1.0f);
	/// - FRandRange(float min, flaot max) : min 과 max 사이의 난수를 반환합니다.
}


// Called when the game starts
void UFloatingMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// - Super : 상위 클래스를 나타냅니다.

	ActorBeginLocation = GetOwner()->GetActorLocation();
	/// - GetOwner() : 해당 컴포넌트를 소유하는 액터를 반환합니다.
	/// - ActorInstance->GetActorLocation() : 액터의 위치를 FVector 형식의 데이터로 반환
}

// Called every frame
void UFloatingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FloatingMovement(DeltaTime);
}

void UFloatingMovementComponent::FloatingMovement(float DeltaTime)
{
	// 현재 액터의 위치를 저장합니다.
	FVector newFloatingLocation = ActorBeginLocation;

	// 다음 Z 좌표를 설정합니다.
	newFloatingLocation.Z = ActorBeginLocation.Z + FMath::Sin(
		(GetWorld()->TimeSeconds + StartTime) * FloatingSpeed * DeltaTime) * FloatingValue;
	/// - FMath : 수학과 관련된 정적 함수들을 제공하는 구조체
	/// - TimeSeconds : 게임이 시작된 후 얼만큼의 시간이 지났는지를 나타냅니다.

	GetOwner()->SetActorLocation(newFloatingLocation);
	/// - SetActorLocation() 액터의 위치를 설정합니다.

}