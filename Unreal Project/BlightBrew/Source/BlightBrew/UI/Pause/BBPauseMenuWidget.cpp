// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Pause/BBPauseMenuWidget.h"

#include "BBPauseScreenWidget.h"
#include "BlightBrew/UI/Settings/BBSettingsWidget.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"

void UBBPauseMenuWidget::SetOwnerCharacter(ABBPlayerCharacter* InCharacter)
{
	PauseScreenWidget->SetOwnerCharacter(InCharacter);
}

ABBPlayerCharacter* UBBPauseMenuWidget::GetOwnerCharacter()
{
	return PauseScreenWidget->GetOwnerCharacter();
}

void UBBPauseMenuWidget::SetCurrentWidget(EPauseWidgetType widget)
{
	switch(widget)
	{
	case EPauseWidgetType::Menu:
		{
		WidgetSwitcher->SetActiveWidget(PauseScreenWidget);
		break;
		}
	case EPauseWidgetType::Settings:
	{
		WidgetSwitcher->SetActiveWidget(SettingsWidget);
		break;
	}
	}
}

void UBBPauseMenuWidget::SetBorderVisibility(ESlateVisibility InVisibility)
{
	Border->SetVisibility(InVisibility);
}

void UBBPauseMenuWidget::Pause()
{
	PauseScreenWidget->Pause();
	Border->SetVisibility(ESlateVisibility::Visible);
}

void UBBPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Border->SetVisibility(ESlateVisibility::Hidden);
}
