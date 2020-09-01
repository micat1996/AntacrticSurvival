// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInst.h"
#include "../PlayerCharacter.h"


void UPlayerCharacterAnimInst::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	UE_LOG(LogTemp, Warning, TEXT("NativeBeginPlay!"));

}

void UPlayerCharacterAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(PlayerCharacter)) return;

	HorizontalSpeed = PlayerCharacter->GetVelocity().Size();

}