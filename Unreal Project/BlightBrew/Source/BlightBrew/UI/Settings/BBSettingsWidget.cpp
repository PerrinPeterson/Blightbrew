// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Settings/BBSettingsWidget.h"

#include "BlightBrew/UI/Pause/BBPauseMenuWidget.h"
#include "BlightBrew/UI/Pause/BBPauseScreenWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UBBSettingsWidget::SwitchActiveWidget(ESettingsWidgetType widgetType)
{
	switch (widgetType)
	{
		case ESettingsWidgetType::Audio:
		{
			WidgetSwitcher->SetActiveWidget(AudioWidget);
			break;
		}
		case ESettingsWidgetType::Control:
		{
			WidgetSwitcher->SetActiveWidget(ControlWidget);
			break;
		}
		case ESettingsWidgetType::Video:
		{
			WidgetSwitcher->SetActiveWidget(VideoWidget);
			break;
		}
		case ESettingsWidgetType::Main:
		{
			WidgetSwitcher->SetActiveWidget(AudioWidget);
			break;
		}
	}
}

void UBBSettingsWidget::ToggleEnabled(bool enabled)
{
	ToggleEnableAndVisibility(enabled);
}

void UBBSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBBSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Border->SetIsEnabled(false);
	//Border->SetVisibility(ESlateVisibility::Hidden);

	//PauseWidget = Cast<UBBPauseScreenWidget>(GetParent()->GetOutermostObject());

	WidgetSwitcher->SetActiveWidget(AudioWidget);

	AudioButton->OnPressed.AddDynamic(this, &UBBSettingsWidget::OnAudioPressed);
	ControlButton->OnPressed.AddDynamic(this, &UBBSettingsWidget::OnControlPressed);
	VideoButton->OnPressed.AddDynamic(this, &UBBSettingsWidget::OnVideoPressed);
	BackButton->OnPressed.AddDynamic(this, &UBBSettingsWidget::OnBackPressed);
}

void UBBSettingsWidget::OnAudioPressed()
{
	SwitchActiveWidget(ESettingsWidgetType::Audio);
}

void UBBSettingsWidget::OnControlPressed()
{
	SwitchActiveWidget(ESettingsWidgetType::Control);
}

void UBBSettingsWidget::OnVideoPressed()
{
	SwitchActiveWidget(ESettingsWidgetType::Video);
}

void UBBSettingsWidget::OnBackPressed()
{
	if (UBBPauseMenuWidget* Parent = Cast<UBBPauseMenuWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		Parent->SetCurrentWidget(EPauseWidgetType::Menu);
	}
	//if(PauseWidget)
	{
		//PauseWidget->GetWidgetSwitcher()->SetActiveWidget(PauseWidget);
		//ToggleEnableAndVisibility(false);
		//PauseWidget->ToggleEnabled(true);
	}
}

void UBBSettingsWidget::ToggleEnableAndVisibility(bool isEnabled)
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
