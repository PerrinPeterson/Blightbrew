// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Pause/BBPauseScreenWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/Settings/BBSettingsWidget.h"
#include "Components/WidgetSwitcher.h"
#include "BlightBrew/UI/Pause/BBPauseMenuWidget.h"

void UBBPauseScreenWidget::ToggleEnabled(bool enabled)
{
	ToggleEnableAndVisibility(enabled);
}

void UBBPauseScreenWidget::Pause()
{
	Border->SetIsEnabled(true);
	Border->SetVisibility(ESlateVisibility::Visible);
}

void UBBPauseScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (OwningCharacter == nullptr)
	{
		return;
	}
	
}

void UBBPauseScreenWidget::NativeConstruct()
{
	Border->SetIsEnabled(false);
	Border->SetVisibility(ESlateVisibility::Hidden);

	//SettingsWidget->SetPauseScreenWidget(this);

	ResumeButton->OnPressed.AddDynamic(this, &UBBPauseScreenWidget::OnResume);
	SettingsButton->OnPressed.AddDynamic(this, &UBBPauseScreenWidget::OnSettings);
	QuitButton->OnPressed.AddDynamic(this, &UBBPauseScreenWidget::OnQuit);
}

void UBBPauseScreenWidget::OnResume()
{
	Border->SetIsEnabled(false);
	Border->SetVisibility(ESlateVisibility::Hidden);

	if (UBBPauseMenuWidget* Parent = Cast<UBBPauseMenuWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		Parent->SetBorderVisibility(ESlateVisibility::Hidden);
	}

	OwningCharacter->UnPause();
}

void UBBPauseScreenWidget::OnSettings()
{
	if(UBBPauseMenuWidget* Parent = Cast<UBBPauseMenuWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		Parent->SetCurrentWidget(EPauseWidgetType::Settings);
	}


	//SettingsWidget->ToggleEnabled(true);
	//ToggleEnableAndVisibility(false);

	//WidgetSwitcher->SetActiveWidget(SettingsWidget);

	
}

void UBBPauseScreenWidget::OnQuit()
{
	//FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(this, "MainMenu", false);
	//UGameplayStatics::LoadStreamLevel(this, "MainMenu", true, true, LatentInfo);
}

void UBBPauseScreenWidget::ToggleEnableAndVisibility(bool isEnabled)
{
	Border->SetIsEnabled(isEnabled);

	if (isEnabled)
	{
		Border->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Border->SetVisibility(ESlateVisibility::Hidden);
	}
}
