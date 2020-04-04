// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterMultiplayerGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTIPLAYER_API ALobbyGameMode : public AShooterMultiplayerGameMode
{
	GENERATED_BODY()

public: 

	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Exiting) override;

private:
	uint32 NumberOfPlayers = 0;

};
