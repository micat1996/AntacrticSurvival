// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AntacrticSurvival.h"
#include "Components/ActorComponent.h"
#include "../../Structures/DropObjectInfo.h"

#include "SpawnDropObjectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANTACRTICSURVIVAL_API USpawnDropObjectComponent : public UActorComponent
{
	GENERATED_BODY()


private :
	class UDataTable* DropObjectDataTable;

	// 현재 딜레이를 저장할 변수
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentDelay;

	// 타이머 핸들을 선언합니다.
	FTimerHandle SpawnTimerHandle;
	// - 실행시킨 타이머를 컨트롤할 때 사용할 수 있습니다.

	// 플레이어 캐릭터를 나타내는 필드입니다.
	UPROPERTY()
	class APlayerCharacter* PlayerCharacterInst;

	UPROPERTY()
	class UASGameInst* GameInst;


public :
	UPROPERTY(EditAnywhere, meta = (ClampMin = 10.0, ClampMax = 50.0, UIMin = 10.0, UIMax = 50.0))
	float FishDropPercentage;

	UPROPERTY(VisibleAnywhere)
	TArray<FDropObjectInfo> FishObjInfos;

	UPROPERTY(VisibleAnywhere)
	TArray<FDropObjectInfo> TrashObjInfos;

	// 플레이어부터 양 끝지점까지의 거리
	UPROPERTY(EditAnywhere)
	float SpawnHalfDistanceX;

	// DropObject 생성 최소 딜레이
	UPROPERTY(EditAnywhere)
		float MinDelay;

	// DropObject 생성 최대 딜레이
	UPROPERTY(EditAnywhere)
		float MaxDelay;

public:	
	USpawnDropObjectComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private :
	void InitializeDropObjectInfos();

	// DropObject 를 생성하는 메서드
	/// - 타이머에 의해 호출됩니다.
	void CreateDropObject();

	// 물고기 생성 확률을 설정합니다.
	FORCEINLINE void SetFishDropPercentage(float percentage)
	{
		FishDropPercentage = FMath::Clamp(percentage, 10.0f, 50.0f);
	}

	// 생성할 DropObject 타입을 반환합니다.
	EDropObjectType GetRandomDropType() const;

	// DropObjType 에 따라 랜덤한 DropObj 정보를 얻습니다.
	FDropObjectInfo GetRandomDropObjInfo(EDropObjectType dropObjType) const;

	// 생성 속도를 점점 더 빠르게 변경합니다.
	void ChangeDelayFaster(float dt);




		
};
