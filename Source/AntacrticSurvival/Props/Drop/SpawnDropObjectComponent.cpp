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

	// DataTable 형식의 애셋을 로드합니다.
	ConstructorHelpers::FObjectFinder<UDataTable> DROP_OBJECT_DATATABLE(
		TEXT("DataTable'/Game/Blueprints/Datatable/DT_DropObjectInfos.DT_DropObjectInfos'"));

	if (DROP_OBJECT_DATATABLE.Succeeded())
		DropObjectDataTable = DROP_OBJECT_DATATABLE.Object;
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("DROP_OBJECT_DATATABLE is not loaded!"));
	}

	// 물고기 생성 확률 설정
	SetFishDropPercentage(10.0f);

	// 딜레이 설정
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

	// 딜레이를 점점 더 빠르게 변경합니다.
	ChangeDelayFaster(DeltaTime);
}


void USpawnDropObjectComponent::InitializeDropObjectInfos()
{
	// 애셋 로드에 성공했는지 확인
	if (!IsValid(DropObjectDataTable)) return;

	// DataTable 에서 행의 이름들을 얻습니다.
	for (FName rowName : DropObjectDataTable->GetRowNames())
	{
		// FindRow 메서드를 이용하여 행 정보를 찾을 때, 문제가 생길 경우
		// 문제 내용을 알릴 문자열 변수를 선언합니다.
		FString contextString;
		FDropObjectInfo* findDropObjInfo = DropObjectDataTable->FindRow<FDropObjectInfo>(rowName, contextString);
		

		// 찾은 데이터의 DropObjectType 이 물고기라면
		if (findDropObjInfo->DropObjectType == EDropObjectType::DT_Fish)
			FishObjInfos.Add(*findDropObjInfo);

		// 타입이 쓰레기라면
		else TrashObjInfos.Add(*findDropObjInfo);
	}
}

void USpawnDropObjectComponent::CreateDropObject()
{
	// 생성할 DropObj 의 타입을 저장합니다.
	auto dropObjType = GetRandomDropType();

	// 생성시킬 DropObj 정보를 저장합니다.
	auto dropObjInfo = GetRandomDropObjInfo(dropObjType);

	// 액터를 생성할 위치를 저장합니다.
	FVector spawnLocation = GetOwner()->GetActorLocation() +
		FMath::FRandRange(-SpawnHalfDistanceX, SpawnHalfDistanceX) * FVector::RightVector;
		
	// 액터를 생성합니다.
	ADropObject* dropObj = GetWorld()->SpawnActor<ADropObject>(
		spawnLocation, FRotator::ZeroRotator);
	/// - SpawnActor<T>() : T 형식의 액터를 생성합니다.

	// 플레이어 캐릭터를 나타내는 변수가 nullptr 라면
	if (!IsValid(PlayerCharacterInst))
		PlayerCharacterInst = GameInst->GetPlayerCharacter();

	// 플레이어 캐릭터 인스턴스가 유효하지 않다면 하단 구문을 실행하지 않습니다.
	if (!IsValid(PlayerCharacterInst))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacterInst is not valid!"));
		return;
	}

	// 생성한 DropObject 초기화
	dropObj->InitializeDropobject(dropObjInfo, PlayerCharacterInst);

	// 게임 오버 상태라면 실행 중단
	if (GameInst->GetGameOver()) return;


	// 타이머를 실행시킵니다.
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, 
		this, &USpawnDropObjectComponent::CreateDropObject, CurrentDelay, false);
	/// - 타이머 : 정의한 시간마다 특정한 동작을 수행하는 기능을 의미합니다.
	/// - 타이머가 수행할 행동을 등록할 때 가능한 형식 : void(void)
}

EDropObjectType USpawnDropObjectComponent::GetRandomDropType() const
{
	return (FMath::FRandRange(1.0f, 100.0f) <= FishDropPercentage) ?
		EDropObjectType::DT_Fish : EDropObjectType::DT_Trash;
}

FDropObjectInfo USpawnDropObjectComponent::GetRandomDropObjInfo(
	EDropObjectType dropObjType) const
{
	// Fish 정보중 랜덤한 정보를 리턴합니다.
	if (dropObjType == EDropObjectType::DT_Fish)
		return (FishObjInfos[FMath::RandRange(0, FishObjInfos.Num() - 1)]);

	// Trash 정보중 랜덤한 정보를 리턴합니다.
	else return (TrashObjInfos[FMath::RandRange(0, TrashObjInfos.Num() - 1)]);
}

void USpawnDropObjectComponent::ChangeDelayFaster(float dt)
{
	// CurrentDelay 가 MaxDelay 만큼 빨라지지 않았다면
	// 점점 더 빠르게 변경힙니다.
	if (CurrentDelay > MaxDelay)
		CurrentDelay -= dt * 0.05f;

	// CurrentDelay 가 MaxDelay 만큼 빨라졌다면
	// 최대 속도로 설정합니다.
	else CurrentDelay = MaxDelay;
}