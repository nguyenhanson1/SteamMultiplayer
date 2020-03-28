// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTIPLAYER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	void Setup(class UMainMenu* Parent, uint32 Index);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UFUNCTION()
	void OnClicked();

	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;
};
