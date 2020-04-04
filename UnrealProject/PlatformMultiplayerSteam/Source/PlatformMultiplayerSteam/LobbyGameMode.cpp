// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;
	
	if (NumberOfPlayers >= 3)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Reached 3 Players"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Blueprint/Maps/ThirdPersonExampleMap?listen");
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}
