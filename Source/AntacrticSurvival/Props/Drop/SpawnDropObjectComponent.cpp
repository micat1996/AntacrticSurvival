// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnDropObjectComponent.h"

//#include "Engine/World.h"
#include "../../GameInstance/ASGameInst.h"
#include "../../PlayerCharacter/PlayerCharacter.h"
#include "DropObject.h"
#include "Engine/DataTable.h"


USpawnDropObjectComponent::USpawnDropObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// DataTable ������ �ּ��� �ε��մϴ�.
	ConstructorHelpers::FObjectFinder<UDataTable> DROP_OBJECT_DATATABLE(
		TEXT("DataTable'/Game/Blueprints/Datatable/DT_DropObjectInfos.DT_DropObjectInfos'"));

	if (DROP_OBJECT_DATATABLE.Succeeded())
		DropObjectDataTable = DROP_OBJECT_DATATABLE.Object;
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("DROP_OBJECT_DATATABLE is not loaded!"));
	}

	// ����� ���� Ȯ�� ����
	SetFishDropPercentage(10.0f);

	// ������ ����
	MinDelay = 1.0f;
	MaxDelay = 0.1f;
}


// Called when the game starts
void USpawnDropObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetGameInstace()
	GameInst = Cast<UASGameInst>(GetOwner()->GetGameInstance());

	InitializeDropObjectInfos();

	CurrentDelay = MinDelay;

	CreateDropObject();


}


// Called every frame
void USpawnDropObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �����̸� ���� �� ������ �����մϴ�.
	ChangeDelayFaster(DeltaTime);
}


void USpawnDropObjectComponent::InitializeDropObjectInfos()
{
	// �ּ� �ε忡 �����ߴ��� Ȯ��
	if (!IsValid(DropObjectDataTable)) return;

	// DataTable ���� ���� �̸����� ����ϴ�.
	for (FName rowName : DropObjectDataTable->GetRowNames())
	{
		// FindRow �޼��带 �̿��Ͽ� �� ������ ã�� ��, ������ ���� ���
		// ���� ������ �˸� ���ڿ� ������ �����մϴ�.
		FString contextString;
		FDropObjectInfo* findDropObjInfo = DropObjectDataTable->FindRow<FDropObjectInfo>(rowName, contextString);
		

		// ã�� �������� DropObjectType �� �������
		if (findDropObjInfo->DropObjectType == EDropObjectType::DT_Fish)
			FishObjInfos.Add(*findDropObjInfo);

		// Ÿ���� ��������
		else TrashObjInfos.Add(*findDropObjInfo);
	}
}

void USpawnDropObjectComponent::CreateDropObject()
{
	// ������ DropObj �� Ÿ���� �����մϴ�.
	auto dropObjType = GetRandomDropType();

	// ������ų DropObj ������ �����մϴ�.
	auto dropObjInfo = GetRandomDropObjInfo(dropObjType);

	// ���͸� ������ ��ġ�� �����մϴ�.
	FVector spawnLocation = GetOwner()->GetActorLocation() +
		FMath::FRandRange(-SpawnHalfDistanceX, SpawnHalfDistanceX) * FVector::RightVector;
		
	// ���͸� �����մϴ�.
	ADropObject* dropObj = GetWorld()->SpawnActor<ADropObject>(
		spawnLocation, FRotator::ZeroRotator);
	/// - SpawnActor<T>() : T ������ ���͸� �����մϴ�.

	// �÷��̾� ĳ���͸� ��Ÿ���� ������ nullptr ���
	if (!IsValid(PlayerCharacterInst))
		PlayerCharacterInst = GameInst->GetPlayerCharacter();

	// �÷��̾� ĳ���� �ν��Ͻ��� ��ȿ���� �ʴٸ� �ϴ� ������ �������� �ʽ��ϴ�.
	if (!IsValid(PlayerCharacterInst))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacterInst is not valid!"));
		return;
	}

	// ������ DropObject �ʱ�ȭ
	dropObj->InitializeDropobject(dropObjInfo, PlayerCharacterInst);

	// ���� ���� ���¶�� ���� �ߴ�
	if (GameInst->GetGameOver()) return;


	// Ÿ�̸Ӹ� �����ŵ�ϴ�.
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, 
		this, &USpawnDropObjectComponent::CreateDropObject, CurrentDelay, false);
	/// - Ÿ�̸� : ������ �ð����� Ư���� ������ �����ϴ� ����� �ǹ��մϴ�.
	/// - Ÿ�̸Ӱ� ������ �ൿ�� ����� �� ������ ���� : void(void)
}

EDropObjectType USpawnDropObjectComponent::GetRandomDropType() const
{
	return (FMath::FRandRange(1.0f, 100.0f) <= FishDropPercentage) ?
		EDropObjectType::DT_Fish : EDropObjectType::DT_Trash;
}

FDropObjectInfo USpawnDropObjectComponent::GetRandomDropObjInfo(
	EDropObjectType dropObjType) const
{
	// Fish ������ ������ ������ �����մϴ�.
	if (dropObjType == EDropObjectType::DT_Fish)
		return (FishObjInfos[FMath::RandRange(0, FishObjInfos.Num() - 1)]);

	// Trash ������ ������ ������ �����մϴ�.
	else return (TrashObjInfos[FMath::RandRange(0, TrashObjInfos.Num() - 1)]);
}

void USpawnDropObjectComponent::ChangeDelayFaster(float dt)
{
	// CurrentDelay �� MaxDelay ��ŭ �������� �ʾҴٸ�
	// ���� �� ������ �������ϴ�.
	if (CurrentDelay > MaxDelay)
		CurrentDelay -= dt * 0.05f;

	// CurrentDelay �� MaxDelay ��ŭ �������ٸ�
	// �ִ� �ӵ��� �����մϴ�.
	else CurrentDelay = MaxDelay;
}