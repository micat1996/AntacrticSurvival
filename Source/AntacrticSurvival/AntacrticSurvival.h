#pragma once

//#include "CoreMinimal.h"
/// - 언리얼 오브젝트가 동작할 수 있는 최소 기능만 선언된 헤더
/// - 해당 헤더 파일은 UE 프로그래밍에 필요한 기본적인 타입, 연산에 대한
///   헤더를 포함합니다.

#include "EngineMinimal.h"


/*
UENUM() UCLASS() USTRUCT() UFUNCTION() UPROPERTY()
"MyCustomActor.generated.h"

UObject(Unreal Object)
언리얼 엔진의 관리를 받는 객체

UHT : UObject 를 지원하는 코드 생성 툴

UObject
- #include "MyCustomActor.generated.h"
- UCLASS()
- 클래스 : U, A, F
- GENERATED_BODY()





C++ 객체가 언리얼 오브젝트가 되는 경우 향상되는 기능
클래스 기본 객체(CDO) : 객체의 초기 값을 자체적으로 관리합니다.
리플렉션  : 런타임중 객체의 정보를 실시간을 조회할 수 있습니다.
GC : 참조되지 않은 객체를 해제합니다.
대리자 : 함수를 묶어서 효과적으로 관리하고 호출할 수 있습니다.

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

FString : 일반적인 문자열을 저장할 수 있는 타입
FName : 어떠한 객체의 이름에 사용되는 타입
FText : 현지화 가능 텍스트에 사용되는 타입

FString -> FText    : FText::FromString()
FString -> FName  : FName(*FStringInst)

FName -> FString  : FText::FromName()
FName -> FText    : FText::FromName()

FText -> FString    : FTextInst.ToString()
FText -> FName    : FName(*FStringInst.ToString())
*/