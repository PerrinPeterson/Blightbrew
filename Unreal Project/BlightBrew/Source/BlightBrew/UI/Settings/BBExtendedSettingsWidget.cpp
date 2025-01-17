// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Settings/BBExtendedSettingsWidget.h"

#include "BlightBrew/UI/MainMenu/BBMainMenuParentWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

class UBBMainMenuParentWidget;

void UBBExtendedSettingsWidget::SwitchActiveWidget(EExtendedSettingsWidgetType widgetType)
{
	switch (widgetType)
	{
		case EExtendedSettingsWidgetType::Audio:
		{
			WidgetSwitcher->SetActiveWidget(AudioWidget);
			break;
		}
		case EExtendedSettingsWidgetType::Control:
		{
			WidgetSwitcher->SetActiveWidget(ControlWidget);
			break;
		}
		case EExtendedSettingsWidgetType::Video:
		{
			WidgetSwitcher->SetActiveWidget(VideoWidget);
			break;
		}
		case EExtendedSettingsWidgetType::Main:
		{
			WidgetSwitcher->SetActiveWidget(AudioWidget);
			break;
		}
	}
}

void UBBExtendedSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBBExtendedSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher->SetActiveWidget(AudioWidget);

	AudioButton->OnPressed.AddDynamic(this, &UBBExtendedSettingsWidget::OnAudioPressed);
	ControlButton->OnPressed.AddDynamic(this, &UBBExtendedSettingsWidget::OnControlPressed);
	VideoButton->OnPressed.AddDynamic(this, &UBBExtendedSettingsWidget::OnVideoPressed);
	BackButton->OnPressed.AddDynamic(this, &UBBExtendedSettingsWidget::OnBackPressed);
}

void UBBExtendedSettingsWidget::OnAudioPressed()
{
	SwitchActiveWidget(EExtendedSettingsWidgetType::Audio);
}

void UBBExtendedSettingsWidget::OnControlPressed()
{
	SwitchActiveWidget(EExtendedSettingsWidgetType::Control);
}

void UBBExtendedSettingsWidget::OnVideoPressed()
{
	SwitchActiveWidget(EExtendedSettingsWidgetType::Video);
}

void UBBExtendedSettingsWidget::OnBackPressed()
{
	if (UBBMainMenuParentWidget* Parent = Cast<UBBMainMenuParentWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Success"));
		Parent->SetCurrentWidget(EMainMenuWidgetType::Menu);
	}
}
