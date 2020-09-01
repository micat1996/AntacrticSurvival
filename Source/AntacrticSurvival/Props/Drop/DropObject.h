// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "GameFramework/Actor.h"
#include "../../Structures/DropObjectInfo.h"
#include "DropObject.generated.h"

UCLASS()
class ANTACRTICSURVIVAL_API ADropObject : public AActor
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VIsibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* RotatingMovement;

	// 오브젝트 정보
	FDropObjectInfo ObjInfo;

	// 떨어지는 속도
	float FallDownSpeed;

	// 플레이어 객체를 나타냅니다.
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;


	
public:	
	ADropObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void InitializeDropobject(const FDropObjectInfo& objInfo,
		class APlayerCharacter* playerCharacter);

private :
	void InitializeComponents();

	// 떨어지는 움직임을 수행합니다.
	void FallDown(float dt);

	UFUNCTION()
	void AddDamage(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	/// - OverlappedComponent : 겹친 자신의 컴포넌트를 나타냅니다.
	/// - OtherActor : 겹친 상대 액터를 나타냅니다.
	/// - OtherComp : 겹친 상대 컴포넌트를 나타냅니다.
	/// - OtherBodyIndex : 여러 컬리전과 겹쳤을 경우 컬리전들을 
	///   구분하기 위한 번호
	/// - bFromSweep : 액터가 이동할 때 sweep 이벤트를 발생시키도록 하여
	///   발생한 이벤트인지를 나타냅니다.
	/// - SweepResult : Sweep 이벤트 발생시 자세한 결과를 담고 있는
	///   데이터가 전달됩니다.





};
