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

	// Fish 타입이라면 회전하지 않도록 합니다.
	RotatingMovement->RotationRate =
		(ObjInfo.DropObjectType == EDropObjectType::DT_Fish) ?
		FRotator::ZeroRotator : FRotator(0.0f, 0.0f, -180.0f);
}

void ADropObject::InitializeComponents()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC_MESH"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(
		TEXT("ROTATING_MOVEMENT"));

	// Collision Presets 를 설정합니다.
	StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));




	SetRootComponent(StaticMeshComponent);

}

void ADropObject::FallDown(float dt)
{
	// 현재 위치에서 아래로 FallDownSpeed 만큼 이동한 위치를 저장할 변수
	FVector newLocation = GetActorLocation() +
		(FVector::DownVector * FallDownSpeed * dt);

	// 위치를 설정합니다.
	SetActorLocation(newLocation);

	// 해당 액터의 Z 위치가 -250 보다 밑으로 이동했다면
	if (newLocation.Z < -250.0f)
	{
		// 해당 액터를 제거합니다.
		Destroy();
		/// - 자신이 아닌 다른 액터를 제거하고 싶은 경우
		///   GetWorld()->DestroyActor() 를 사용합니다.
	}
}

void ADropObject::AddDamage(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 겹친 액터가 플레이어가 아닌지 확인합니다.
	//if (!(OtherActor->GetClass()->IsChildOf<APlayerCharacter>())) return;
	if (OtherActor != PlayerCharacter) return;

	// 가할 대미지 / 증가시킬 체력을 정의합니다.
	float addDamage = (ObjInfo.DropObjectType == EDropObjectType::DT_Fish) ?
		ObjInfo.ChangeHungryValue : -ObjInfo.ChangeHungryValue;

	// 플레이어에게 대미지를 가합니다.
	UGameplayStatics::ApplyDamage(PlayerCharacter, addDamage,
		nullptr, this, UDamageType::StaticClass());
	/// - DamagedActor 에 전달한 객체에게 대미지를 가합니다.
	///   이 때 상대 객체의 OnTakeAnyDamage 대리자가 호출됩니다.
	/// - AActor *					DamagedActor : 대미지를 가할 액터를 나타냅니다.
	/// - float						BaseDamage : 가할 대미지를 나타냅니다.
	/// - AController *				EventInstigator : 피해를 가한 컨트롤러를 나타냅니다.
	/// - AActor *					DamageCauser : 피해를 입히는 객체를 나타냅니다.
	/// - USubclassOf<UDamageType>	DamageTypeClass : 대미지 타입을 설명하는 UClass 입니다.

	// 해당 액터를 제거합니다.
	Destroy();
}