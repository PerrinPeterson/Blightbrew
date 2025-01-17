// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/Player/BBMainMenuCharacter.h"

#include "Blueprint/UserWidget.h"

#include "BlightBrew/UI/MainMenu/BBMainMenuParentWidget.h"

ABBMainMenuCharacter::ABBMainMenuCharacter()
{

}

void ABBMainMenuCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->Possess(this);

	MainMenuWidget = CreateWidget<UBBMainMenuParentWidget>(GetWorld(), MainMenuClass);
	MainMenuWidget->AddToViewport();

	APlayerController* control = Cast<APlayerController>(Controller);
	control->SetPause(true);
	control->SetInputMode(FInputModeUIOnly());
	control->SetShowMouseCursor(true);
}
