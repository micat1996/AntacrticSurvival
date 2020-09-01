// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropObjectType.generated.h"

// ���� Ÿ���� �����մϴ�.
/// - BlueprintType : �������Ʈ������ ����� �� �ֵ��� �մϴ�.
/// - Unreal C++ �� �̿��Ͽ� �������Ʈ������ ��� ������ ���� Ÿ���� ������ ��
///   �״� BlueprintType �� �Բ� ������� Ÿ���� uint8 �������� �����մϴ�.
UENUM(BlueprintType)
enum class EDropObjectType : uint8
{
	DT_Trash UMETA(DisplayName = "Trash"),
	DT_Fish  UMETA(DisplayName = "Fish")
};

// UMETA()
/// - Ŭ������ �������̽�, ����ü, ���� Ÿ��, ���� Ÿ�� ���, �Լ�, �Ӽ� ����
///   �����ϴ� ����� ������ �� ����ϴ� ��Ÿ������ �������Դϴ�.
