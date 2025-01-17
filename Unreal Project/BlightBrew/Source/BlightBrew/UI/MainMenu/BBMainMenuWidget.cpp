// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/MainMenu/BBMainMenuWidget.h"

#include "BBMainMenuParentWidget.h"
#include "Components/Button.h"

#include "BlightBrew/UI/Pause/BBPauseScreenWidget.h"
#include "Kismet/GameplayStatics.h"

void UBBMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBBMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton->OnPressed.AddDynamic(this, &UBBMainMenuWidget::OnNew);
	LoadGameButton->OnPressed.AddDynamic(this, &UBBMainMenuWidget::OnLoad);
	SettingsButton->OnPressed.AddDynamic(this, &UBBMainMenuWidget::OnSettings);
	CreditsButton->OnPressed.AddDynamic(this, &UBBMainMenuWidget::OnCredits);
	QuitButton->OnPressed.AddDynamic(this, &UBBMainMenuWidget::OnQuit);
}

void UBBMainMenuWidget::OnNew()
{
	UGameplayStatics::OpenLevel(this, "ForestLevel", false);
}

void UBBMainMenuWidget::OnLoad()
{

}

void UBBMainMenuWidget::OnSettings()
{
	if (UBBMainMenuParentWidget* Parent = Cast<UBBMainMenuParentWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		Parent->SetCurrentWidget(EMainMenuWidgetType::Settings);
	}
}

void UBBMainMenuWidget::OnCredits()
{
	if (UBBMainMenuParentWidget* Parent = Cast<UBBMainMenuParentWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		Parent->SetCurrentWidget(EMainMenuWidgetType::Credits);
	}
}

void UBBMainMenuWidget::OnQuit()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
