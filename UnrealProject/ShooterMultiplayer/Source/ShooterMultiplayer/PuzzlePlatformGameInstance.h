// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTIPLAYER_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu();

	virtual void Init();

	UFUNCTION(Exec)
	void Host() ;
	UFUNCTION(Exec)
	void Join(const FString& Address);

	virtual void LoadMainMenu();

private:
	TSubclassOf<class UMenuWidget_Base> MenuClass;
	TSubclassOf<class UMenuWidget_Base> PauseMenuClass;
	class UMainMenu* Menu;
};
