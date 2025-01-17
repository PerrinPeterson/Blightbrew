// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBPauseMenuWidget.generated.h"

class UBBSettingsWidget;
class UBBPauseScreenWidget;
class ABBPlayerCharacter;
class UWidgetSwitcher;
class UBorder;

UENUM()
enum class EPauseWidgetType
{
	Menu,
	Settings,
};

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter);

	ABBPlayerCharacter* GetOwnerCharacter();

	void SetCurrentWidget(EPauseWidgetType widget);

	void SetBorderVisibility(ESlateVisibility InVisibility);

	void Pause();
protected:
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UBBPauseScreenWidget* PauseScreenWidget;

	UPROPERTY(meta = (BindWidget))
		UBBSettingsWidget* SettingsWidget;

	void NativeConstruct() override;
	
};
