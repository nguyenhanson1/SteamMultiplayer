// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget_Base.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer) 
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr)) return;
	PauseMenuClass = PauseMenuBPClass.Class;

}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	if (!ensure(MenuClass!= nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu->SetUp();
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu->SetMenuInterface(this);
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadPauseMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	UMenuWidget_Base* PauseMenu = CreateWidget<UMenuWidget_Base>(this, PauseMenuClass);
	
	if (!ensure(PauseMenu != nullptr)) return;

	PauseMenu->SetUp();

	PauseMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(TEXT("/Game/Blueprint/Maps/Menu"), ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::Init() {
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found System %s"), *Subsystem->GetSubsystemName().ToString());
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Found Session Interface!"));
			
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found No SubSystem"));
	}
}

void UPuzzlePlatformGameInstance::Host() 
{
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Blueprint/Maps/ThirdPersonExampleMap?listen");


}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}