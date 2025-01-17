// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBMainMenuWidget.h"
#include "BlightBrew/UI/Settings/BBSettingsWidget.h"
#include "Blueprint/UserWidget.h"
#include "BBMainMenuParentWidget.generated.h"

class UBBCreditsMenuWidget;
UENUM()
enum class EMainMenuWidgetType
{
	Menu,
	Settings,
	Credits,
	New,
	Load
};

class UBBExtendedSettingsWidget;
class UWidgetSwitcher;
class UBorder;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBMainMenuParentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCurrentWidget(EMainMenuWidgetType widget);


protected:
	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
		UBBMainMenuWidget* MainMenuWidget;

	UPROPERTY(meta = (BindWidget))
		UBBExtendedSettingsWidget* SettingsWidget;

	UPROPERTY(meta = (BindWidget))
		UBBCreditsMenuWidget* CreditsMenuWidget;

};
