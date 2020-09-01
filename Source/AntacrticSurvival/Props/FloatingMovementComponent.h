// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "Components/ActorComponent.h"
#include "FloatingMovementComponent.generated.h"
/// - UHT 에 의해 자동으로 생성되는 부가 파일입니다.
/// - 헤더 포함 구문 최 하단에 작성해야 합니다.


// UCLASS()
/// - 해당 클래스가 UObject 임을 선언합니다.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANTACRTICSURVIVAL_API UFloatingMovementComponent : public UActorComponent
{
	GENERATED_BODY()
		/// - 항상 클래스 첫 줄에 작성되어야 하며,
		///   클래스가 엔진에 필요한 인프라를 지원하도록 구성합니다.

//private :
public :
	// 필드에 UPROPERTY() 가 사용된다면
	// 리플렉션 시스템에 등록됩니다.
	/// - EditAnywhere : 에디터의 디테일 창에서 편집이 가능함을 의미합니다.
	/// - VisibleAnywhere : 에디터의 디테일 창에서 읽기 전용으로 사용됩니다.
	UPROPERTY(EditAnywhere)
	float FloatingSpeed;

	UPROPERTY(EditAnywhere)
	float FloatingValue;

	UPROPERTY()
	float StartTime;

	UPROPERTY(VisibleAnywhere)
	FVector ActorBeginLocation;

public:	
	// 해당 클래스의 생성자입니다.
	UFloatingMovementComponent();

protected:
	// 게임이 시작될 때나 스폰되었을 경우 한 번 호출되는 메서드입니다.
	virtual void BeginPlay() override;

public:	
	// 매 프레임마다 호출되는 메서드입니다.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// 둥둥 뜨는 움직임을 구현합니다.
	void FloatingMovement(float DeltaTime);

		
};
