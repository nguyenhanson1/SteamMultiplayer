// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"

bool UPauseMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::ClosePauseMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::ToMainMenu);

	return true;
}

void UPauseMenu::ClosePauseMenu()
{
	TearDown();
}

void UPauseMenu::ToMainMenu()
{
	if (MenuInterface != nullptr) {
		TearDown();
		MenuInterface->LoadMainMenu();
	}
	
}
