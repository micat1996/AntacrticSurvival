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

	// �ִ� ���� �̵� �ӵ��� �����մϴ�.
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;

	// ������� �Ծ��� ��� ȣ���� �޼��带 ���ε��մϴ�.
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
	/// - ConstructorHelpers : �����ڿ��� Resource �� Blueprint Class �� �ҷ����� �۾��� 
	///   �����ִ� ����� �����ϴ� Ŭ�����Դϴ�.
	/// - ConstructorHelpers::FObjectFinder : Asset �� ���빰�� ������ �� ����ϴ� ����

	// �ش� Asset �� ���������� �ε��ߴٸ�
	if (SK_BODY.Succeeded())
	{
		// ĳ���� Mesh �� �ε��� �ּ����� �����մϴ�.
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);

		// ����� �������� �����մϴ�.
		GetMesh()->SetRelativeScale3D(FVector::OneVector * 0.7f);

		// ��ġ�� ȸ���� �����մϴ�.
		//GetMesh()->SetRelativeLocation(FVector::UpVector * -90.0f);
		//GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeLocationAndRotation(
			FVector::UpVector * -90.0f,
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
	{
		// �ε忡 ������ ��� �α� ����
		UE_LOG(LogTemp, Error, TEXT("SK_BODY not Loaded!"));
	}

	// UHorizontalMovementComponent �߰�
	HorizontalMovement = CreateDefaultSubobject<UHorizontalMovementComponent>(
		TEXT("HORIZONTAL_MOVEMENT"));

	static ConstructorHelpers::FClassFinder<UPlayerCharacterAnimInst> ANIM_PLAYER(
		TEXT("AnimBlueprint'/Game/Blueprints/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));
	// ConstructorHelpers::FClassFinder : UClass �� ������ �� ����մϴ�.
	/// - ��� �� �ڿ� _C �� �ۼ��մϴ�.


	if (ANIM_PLAYER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimInstanceClass = ANIM_PLAYER.Class);
		/// - SkeletalMeshComponent Instance -> SetAnimInstanceClass(AnimInstance UClass)
		///   SkeletalMeshComponent Instance �� ����� AnimInstance Class �� 
		///   AnimInstance UClass �� �����մϴ�.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ANIM_PLAYER is not loaded!!!"));
	}

	// ��Ʈ�ѷ��� Yaw ȸ������ ����ϵ��� �մϴ�.
	bUseControllerRotationYaw = true;
}

void APlayerCharacter::OnHit(
	AActor*						DamagedActor,
	float						Damage,
	const class UDamageType*	DamageType,
	class AController*			InstigatedBy,
	AActor*						DamageCauser)
{
	// ����� �������� �����ŵ�ϴ�.
	AddHungryValue(Damage);

	// ������ ���� / ���� ��ŵ�ϴ�.
	GameInst->AddScore(Damage);

	UE_LOG(LogTemp, Warning, TEXT("[ HP : %.2f ]   [ Score : %.2f ]"),
		HungryValue, GameInst->GetScore());
}
void APlayerCharacter::AddHungryValue(float addValue)
{
	// ���� ������� ���� ���
	if (GameInst->GetGameOver()) return;

	HungryValue += addValue;

	// ���� ����� ��ġ�� 0 �̶�� ���� ����
	if (HungryValue < 0.0f)
		GameInst->SetGameOver(true);

	// HungryValue �� ���� 0 ~ 100 ������ ������ ���Ӵϴ�.
	HungryValue = FMath::Clamp(HungryValue, 0.0f, 100.0f);
}