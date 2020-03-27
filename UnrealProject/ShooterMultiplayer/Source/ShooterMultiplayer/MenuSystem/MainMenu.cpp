// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "MenuWidget_Base.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	ServerRowClass = ServerRowBPClass.Class;
}

bool UMainMenu::Initialize() {

	bool Success = Super::Initialize();
	if (!Success) return false;
	
	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

	return true;
}

void UMainMenu::HostServer()
{
	if (this->MenuInterface != nullptr) {
		this->MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer() {
	
	if (MenuInterface != nullptr)
	{
		/*if (!ensure(IPAddressField != nullptr)) return;
		const FString& Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);*/
		UWorld* World = this->GetWorld();
		if (!ensure(World != nullptr)) return;

		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(World != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
