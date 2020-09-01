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

	// ������Ʈ ����
	FDropObjectInfo ObjInfo;

	// �������� �ӵ�
	float FallDownSpeed;

	// �÷��̾� ��ü�� ��Ÿ���ϴ�.
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

	// �������� �������� �����մϴ�.
	void FallDown(float dt);

	UFUNCTION()
	void AddDamage(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	/// - OverlappedComponent : ��ģ �ڽ��� ������Ʈ�� ��Ÿ���ϴ�.
	/// - OtherActor : ��ģ ��� ���͸� ��Ÿ���ϴ�.
	/// - OtherComp : ��ģ ��� ������Ʈ�� ��Ÿ���ϴ�.
	/// - OtherBodyIndex : ���� �ø����� ������ ��� �ø������� 
	///   �����ϱ� ���� ��ȣ
	/// - bFromSweep : ���Ͱ� �̵��� �� sweep �̺�Ʈ�� �߻���Ű���� �Ͽ�
	///   �߻��� �̺�Ʈ������ ��Ÿ���ϴ�.
	/// - SweepResult : Sweep �̺�Ʈ �߻��� �ڼ��� ����� ��� �ִ�
	///   �����Ͱ� ���޵˴ϴ�.





};
