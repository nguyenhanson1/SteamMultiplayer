// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget_Base.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTIPLAYER_API UPauseMenu : public UMenuWidget_Base
{
	GENERATED_BODY()
protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;
	

	UFUNCTION()
		void ClosePauseMenu();
	UFUNCTION()
		void ToMainMenu();
};
