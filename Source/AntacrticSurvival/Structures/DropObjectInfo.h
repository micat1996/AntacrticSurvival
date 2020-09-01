// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Enums/DropObjectType.h"

#include "DropObjectInfo.generated.h"



// DataTable 생성시 기반 형태로 사용될 구조체를 선언합니다.
/// - DataTable : 게임 개발시 개발자 뿐만이 아닌, 기획자도 손쉽게 바꿀 수 있어야 하는
///   데이터들을 나열하여 보여주는 애셋을 의미합니다.
USTRUCT(BlueprintType)
struct ANTACRTICSURVIVAL_API FDropObjectInfo : public FTableRowBase
{
	//GENERATED_USTRUCT_BODY()
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDropObjectType DropObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* DropObjectStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChangeHungryValue;

public:
	FDropObjectInfo();
};
