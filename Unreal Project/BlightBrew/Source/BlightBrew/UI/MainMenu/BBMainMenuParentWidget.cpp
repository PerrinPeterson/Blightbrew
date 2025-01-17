// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/MainMenu/BBMainMenuParentWidget.h"


#include "BlightBrew/UI/Settings/BBExtendedSettingsWidget.h"
#include "BlightBrew/UI/MainMenu/BBCreditsMenuWidget.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"

void UBBMainMenuParentWidget::SetCurrentWidget(EMainMenuWidgetType widget)
{
	switch (widget)
	{
		case EMainMenuWidgetType::Menu:
		{
			WidgetSwitcher->SetActiveWidget(MainMenuWidget);
			break;
		}
		case EMainMenuWidgetType::Settings:
		{
			WidgetSwitcher->SetActiveWidget(SettingsWidget);
			break;
		}
		case EMainMenuWidgetType::Credits:
		{
			WidgetSwitcher->SetActiveWidget(CreditsMenuWidget);
			break;
		}
	}
}
