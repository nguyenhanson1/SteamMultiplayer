// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
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
	void Host(FString ServerName) ;
	UFUNCTION(Exec)
	void Join(uint32 Index);

	virtual void LoadMainMenu();

	void RefreshServerList() override;

	void StartSession();


private:
	TSubclassOf<class UMenuWidget_Base> MenuClass;
	TSubclassOf<class UMenuWidget_Base> PauseMenuClass;
	
	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void FOnCreateSessionComplete(FName SessionName, bool Success);

	void FOnDestroySessionComplete(FName SessionName, bool Success);

	void FOnFindSessionsComplete(bool Success);

	void FOnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	FString DesiredServerName;
	void CreateSession();

};
