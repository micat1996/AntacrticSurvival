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

	// ���� �����̸� ������ ����
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentDelay;

	// Ÿ�̸� �ڵ��� �����մϴ�.
	FTimerHandle SpawnTimerHandle;
	// - �����Ų Ÿ�̸Ӹ� ��Ʈ���� �� ����� �� �ֽ��ϴ�.

	// �÷��̾� ĳ���͸� ��Ÿ���� �ʵ��Դϴ�.
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

	// �÷��̾���� �� ������������ �Ÿ�
	UPROPERTY(EditAnywhere)
	float SpawnHalfDistanceX;

	// DropObject ���� �ּ� ������
	UPROPERTY(EditAnywhere)
		float MinDelay;

	// DropObject ���� �ִ� ������
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

	// DropObject �� �����ϴ� �޼���
	/// - Ÿ�̸ӿ� ���� ȣ��˴ϴ�.
	void CreateDropObject();

	// ����� ���� Ȯ���� �����մϴ�.
	FORCEINLINE void SetFishDropPercentage(float percentage)
	{
		FishDropPercentage = FMath::Clamp(percentage, 10.0f, 50.0f);
	}

	// ������ DropObject Ÿ���� ��ȯ�մϴ�.
	EDropObjectType GetRandomDropType() const;

	// DropObjType �� ���� ������ DropObj ������ ����ϴ�.
	FDropObjectInfo GetRandomDropObjInfo(EDropObjectType dropObjType) const;

	// ���� �ӵ��� ���� �� ������ �����մϴ�.
	void ChangeDelayFaster(float dt);




		
};
