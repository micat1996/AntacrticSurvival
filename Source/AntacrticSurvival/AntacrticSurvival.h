#pragma once

//#include "CoreMinimal.h"
/// - �𸮾� ������Ʈ�� ������ �� �ִ� �ּ� ��ɸ� ����� ���
/// - �ش� ��� ������ UE ���α׷��ֿ� �ʿ��� �⺻���� Ÿ��, ���꿡 ����
///   ����� �����մϴ�.

#include "EngineMinimal.h"


/*
UENUM() UCLASS() USTRUCT() UFUNCTION() UPROPERTY()
"MyCustomActor.generated.h"

UObject(Unreal Object)
�𸮾� ������ ������ �޴� ��ü

UHT : UObject �� �����ϴ� �ڵ� ���� ��

UObject
- #include "MyCustomActor.generated.h"
- UCLASS()
- Ŭ���� : U, A, F
- GENERATED_BODY()





C++ ��ü�� �𸮾� ������Ʈ�� �Ǵ� ��� ���Ǵ� ���
Ŭ���� �⺻ ��ü(CDO) : ��ü�� �ʱ� ���� ��ü������ �����մϴ�.
���÷���  : ��Ÿ���� ��ü�� ������ �ǽð��� ��ȸ�� �� �ֽ��ϴ�.
GC : �������� ���� ��ü�� �����մϴ�.
�븮�� : �Լ��� ��� ȿ�������� �����ϰ� ȣ���� �� �ֽ��ϴ�.

int8   	- __int8
int16 	- __int16
int32 	- __int32
int64 	- __int64

uint8	- unsigned __int8
uint16	- unsigned __int16
uint32	- unsigned __int32
uint64	- unsigned __int64

TCHAR 	- char / wchar_t
FString / FName / FText

FString : �Ϲ����� ���ڿ��� ������ �� �ִ� Ÿ��
FName : ��� ��ü�� �̸��� ���Ǵ� Ÿ��
FText : ����ȭ ���� �ؽ�Ʈ�� ���Ǵ� Ÿ��

FString -> FText    : FText::FromString()
FString -> FName  : FName(*FStringInst)

FName -> FString  : FText::FromName()
FName -> FText    : FText::FromName()

FText -> FString    : FTextInst.ToString()
FText -> FName    : FName(*FStringInst.ToString())
*/