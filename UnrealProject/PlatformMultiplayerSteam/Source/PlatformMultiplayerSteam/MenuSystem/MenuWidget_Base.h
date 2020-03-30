// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget_Base.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTIPLAYER_API UMenuWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(class IMenuInterface* MenuInterface);

	void SetUp();
	void TearDown();

protected:
	IMenuInterface* MenuInterface;
};
