#pragma once

#include "AntacrticSurvival.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ANTACRTICSURVIVAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private :
	// 플레이어 컨트롤러를 나타냅니다.
	class AGamePlayerController* PlayerContrller;

	// 배고픔 수치를 나타냅니다.
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

	/// - 프로젝트 세팅 -> 입력에 매핑한 키 입력 이벤트를 폰에 등록합니다.
	/// - UInputComponent : 액터에 입력 이벤트를 등록하는 기능을 제공하는 컴포넌트입니다.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class AGamePlayerController * GetPlayerController() const
	{ return PlayerContrller; }

	FORCEINLINE float GetHungryValue() const
	{ return HungryValue; }

private :
	void InitializeComponents();

	// 대미지를 입었을 경우 호출될 메서드
	UFUNCTION()
	void OnHit(
		AActor*						DamagedActor,
		float						Damage,
		const class UDamageType*	DamageType,
		class AController*			InstigatedBy,
		AActor*						DamageCauser);
	/// - DamagedActor : 대미지를 입은 액터를 나타냅니다.
	/// - Damage : 입은 피해를 나타냅니다.
	/// - DamageType : 대미지 타입이 전달됩니다.
	/// - InstigatedBy : 피해를 준 컨트롤러가 전달됩니다.
	/// - DamageCauser : 피해를 준 액터가 전달됩니다.

	// 배고픔 수치에 특정한 값을 더합니다.
	void AddHungryValue(float addValue);

};
