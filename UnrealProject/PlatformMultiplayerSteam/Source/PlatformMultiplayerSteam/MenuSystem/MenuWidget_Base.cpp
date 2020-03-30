// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget_Base.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UMenuWidget_Base::SetUp()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget_Base::TearDown()
{
	this->RemoveFromViewport();
	FInputModeGameOnly InputModeData;
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeGame;
	PlayerController->SetInputMode(InputModeGame);

	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget_Base::SetMenuInterface(IMenuInterface* MenuInterface) {
	this->MenuInterface = MenuInterface;
}