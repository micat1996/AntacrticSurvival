// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Enums/DropObjectType.h"

#include "DropObjectInfo.generated.h"



// DataTable ������ ��� ���·� ���� ����ü�� �����մϴ�.
/// - DataTable : ���� ���߽� ������ �Ӹ��� �ƴ�, ��ȹ�ڵ� �ս��� �ٲ� �� �־�� �ϴ�
///   �����͵��� �����Ͽ� �����ִ� �ּ��� �ǹ��մϴ�.
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
