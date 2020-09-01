// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTACRTICSURVIVAL_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeOnInitialized() override;

	
};
