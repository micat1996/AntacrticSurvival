// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "../GameInstance/ASGameInst.h"
#include "../Controller/GamePlayerController.h"
#include "HorizontalMovementComponent/HorizontalMovementComponent.h"
#include "PlayerCharacterAnimInst/PlayerCharacterAnimInst.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HungryValue = 50.0f;

	InitializeComponents();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UASGameInst>(GetGameInstance());

	PlayerContrller = Cast<AGamePlayerController>(GetController());

	// 최대 지면 이동 속도를 설정합니다.
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;

	// 대미지를 입었을 경우 호출할 메서드를 바인딩합니다.
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::OnHit);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddHungryValue(DeltaTime * -2.0f);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::InitializeComponents()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("SkeletalMesh'/Game/Resources/Character/SK_Penguin.SK_Penguin'"));
	/// - ConstructorHelpers : 생성자에서 Resource 나 Blueprint Class 를 불러오는 작업을 
	///   도와주는 기능을 제공하는 클래스입니다.
	/// - ConstructorHelpers::FObjectFinder : Asset 의 내용물을 가져올 때 사용하는 형식

	// 해당 Asset 을 성공적으로 로드했다면
	if (SK_BODY.Succeeded())
	{
		// 캐릭터 Mesh 를 로드한 애셋으로 설정합니다.
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);

		// 상대적 스케일을 설정합니다.
		GetMesh()->SetRelativeScale3D(FVector::OneVector * 0.7f);

		// 위치와 회전을 설정합니다.
		//GetMesh()->SetRelativeLocation(FVector::UpVector * -90.0f);
		//GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::UpVector * -90.0f,
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
	{
		// 로드에 실패한 경우 로그 띄우기
		UE_LOG(LogTemp, Error, TEXT("SK_BODY not Loaded!"));
	}

	// UHorizontalMovementComponent 추가
	HorizontalMovement = CreateDefaultSubobject<UHorizontalMovementComponent>(
		TEXT("HORIZONTAL_MOVEMENT"));

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInst> ANIM_PLAYER(
		TEXT("AnimBlueprint'/Game/Blueprints/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));
	// ConstructorHelpers::FClassFinder : UClass 를 가져올 때 사용합니다.
	/// - 경로 맨 뒤에 _C 를 작성합니다.


	if (ANIM_PLAYER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimInstanceClass = ANIM_PLAYER.Class);
		/// - SkeletalMeshComponent Instance -> SetAnimInstanceClass(AnimInstance UClass)
		///   SkeletalMeshComponent Instance 가 사용할 AnimInstance Class 를 
		///   AnimInstance UClass 로 설정합니다.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ANIM_PLAYER is not loaded!!!"));
	}

	// 컨트롤러의 Yaw 회전값을 사용하도록 합니다.
	bUseControllerRotationYaw = true;
}

void APlayerCharacter::OnHit(
	AActor*						DamagedActor,
	float						Damage,
	const class UDamageType*	DamageType,
	class AController*			InstigatedBy,
	AActor*						DamageCauser)
{
	// 배고픔 게이지를 변경시킵니다.
	AddHungryValue(Damage);

	// 점수를 증가 / 감소 시킵니다.
	GameInst->AddScore(Damage);

	UE_LOG(LogTemp, Warning, TEXT("[ HP : %.2f ]   [ Score : %.2f ]"),
		HungryValue, GameInst->GetScore());
}
void APlayerCharacter::AddHungryValue(float addValue)
{
	// 게임 오버라면 실행 취소
	if (GameInst->GetGameOver()) return;

	HungryValue += addValue;

	// 만약 배고픔 수치가 0 이라면 게임 오버
	if (HungryValue < 0.0f)
		GameInst->SetGameOver(true);

	// HungryValue 의 값을 0 ~ 100 사이의 값으로 가둡니다.
	HungryValue = FMath::Clamp(HungryValue, 0.0f, 100.0f);
}