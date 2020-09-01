#pragma once

#include "AntacrticSurvival.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ANTACRTICSURVIVAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private :
	// �÷��̾� ��Ʈ�ѷ��� ��Ÿ���ϴ�.
	class AGamePlayerController* PlayerContrller;

	// ����� ��ġ�� ��Ÿ���ϴ�.
	float HungryValue;

	UPROPERTY()
	class UASGameInst* GameInst;

	
public :
	TSubclassOf<class UPlayerCharacterAnimInst> PlayerAnimInstanceClass;

public :
	UPROPERTY(VisibleAnywhere)
	class UHorizontalMovementComponent* HorizontalMovement;


public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/// - ������Ʈ ���� -> �Է¿� ������ Ű �Է� �̺�Ʈ�� ���� ����մϴ�.
	/// - UInputComponent : ���Ϳ� �Է� �̺�Ʈ�� ����ϴ� ����� �����ϴ� ������Ʈ�Դϴ�.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class AGamePlayerController * GetPlayerController() const
	{ return PlayerContrller; }

	FORCEINLINE float GetHungryValue() const
	{ return HungryValue; }

private :
	void InitializeComponents();

	// ������� �Ծ��� ��� ȣ��� �޼���
	UFUNCTION()
	void OnHit(
		AActor*						DamagedActor,
		float						Damage,
		const class UDamageType*	DamageType,
		class AController*			InstigatedBy,
		AActor*						DamageCauser);
	/// - DamagedActor : ������� ���� ���͸� ��Ÿ���ϴ�.
	/// - Damage : ���� ���ظ� ��Ÿ���ϴ�.
	/// - DamageType : ����� Ÿ���� ���޵˴ϴ�.
	/// - InstigatedBy : ���ظ� �� ��Ʈ�ѷ��� ���޵˴ϴ�.
	/// - DamageCauser : ���ظ� �� ���Ͱ� ���޵˴ϴ�.

	// ����� ��ġ�� Ư���� ���� ���մϴ�.
	void AddHungryValue(float addValue);

};
