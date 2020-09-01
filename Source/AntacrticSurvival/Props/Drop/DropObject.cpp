// Fill out your copyright notice in the Description page of Project Settings.


#include "DropObject.h"
#include "../../PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/DamageType.h"


ADropObject::ADropObject()
{
	PrimaryActorTick.bCanEverTick = true;

	FallDownSpeed = 700.0f;

	InitializeComponents();
}

// Called when the game starts or when spawned
void ADropObject::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
		this, &ADropObject::AddDamage);
}

// Called every frame
void ADropObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FallDown(DeltaTime);

}

void ADropObject::InitializeDropobject(const FDropObjectInfo& objInfo,
	class APlayerCharacter* playerCharacter)
{
	ObjInfo = objInfo;
	PlayerCharacter = playerCharacter;
	StaticMeshComponent->SetStaticMesh(ObjInfo.DropObjectStaticMesh);

	// Fish Ÿ���̶�� ȸ������ �ʵ��� �մϴ�.
	RotatingMovement->RotationRate =
		(ObjInfo.DropObjectType == EDropObjectType::DT_Fish) ?
		FRotator::ZeroRotator : FRotator(0.0f, 0.0f, -180.0f);
}

void ADropObject::InitializeComponents()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC_MESH"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(
		TEXT("ROTATING_MOVEMENT"));

	// Collision Presets �� �����մϴ�.
	StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));




	SetRootComponent(StaticMeshComponent);

}

void ADropObject::FallDown(float dt)
{
	// ���� ��ġ���� �Ʒ��� FallDownSpeed ��ŭ �̵��� ��ġ�� ������ ����
	FVector newLocation = GetActorLocation() +
		(FVector::DownVector * FallDownSpeed * dt);

	// ��ġ�� �����մϴ�.
	SetActorLocation(newLocation);

	// �ش� ������ Z ��ġ�� -250 ���� ������ �̵��ߴٸ�
	if (newLocation.Z < -250.0f)
	{
		// �ش� ���͸� �����մϴ�.
		Destroy();
		/// - �ڽ��� �ƴ� �ٸ� ���͸� �����ϰ� ���� ���
		///   GetWorld()->DestroyActor() �� ����մϴ�.
	}
}

void ADropObject::AddDamage(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// ��ģ ���Ͱ� �÷��̾ �ƴ��� Ȯ���մϴ�.
	//if (!(OtherActor->GetClass()->IsChildOf<APlayerCharacter>())) return;
	if (OtherActor != PlayerCharacter) return;

	// ���� ����� / ������ų ü���� �����մϴ�.
	float addDamage = (ObjInfo.DropObjectType == EDropObjectType::DT_Fish) ?
		ObjInfo.ChangeHungryValue : -ObjInfo.ChangeHungryValue;

	// �÷��̾�� ������� ���մϴ�.
	UGameplayStatics::ApplyDamage(PlayerCharacter, addDamage,
		nullptr, this, UDamageType::StaticClass());
	/// - DamagedActor �� ������ ��ü���� ������� ���մϴ�.
	///   �� �� ��� ��ü�� OnTakeAnyDamage �븮�ڰ� ȣ��˴ϴ�.
	/// - AActor *					DamagedActor : ������� ���� ���͸� ��Ÿ���ϴ�.
	/// - float						BaseDamage : ���� ������� ��Ÿ���ϴ�.
	/// - AController *				EventInstigator : ���ظ� ���� ��Ʈ�ѷ��� ��Ÿ���ϴ�.
	/// - AActor *					DamageCauser : ���ظ� ������ ��ü�� ��Ÿ���ϴ�.
	/// - USubclassOf<UDamageType>	DamageTypeClass : ����� Ÿ���� �����ϴ� UClass �Դϴ�.

	// �ش� ���͸� �����մϴ�.
	Destroy();
}