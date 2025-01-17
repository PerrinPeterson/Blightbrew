// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBSettingsWidget.generated.h"

class UBBPauseScreenWidget;
class UButton;
class UBorder;
class UUserWidget;
class UWidgetSwitcher;
class UTextBlock;

UENUM()
enum class ESettingsWidgetType
{
	Audio,
	Control,
	Video,
	Main,
};

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchActiveWidget(ESettingsWidgetType widgetType);

	void ToggleEnabled(bool enabled);

protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
		UUserWidget* AudioWidget;

	UPROPERTY(meta = (BindWidget))
		UUserWidget* ControlWidget;

	UPROPERTY(meta = (BindWidget))
		UUserWidget* VideoWidget;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UButton* AudioButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ControlButton;

	UPROPERTY(meta = (BindWidget))
		UButton* VideoButton;

	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnAudioPressed();

	UFUNCTION()
		void OnControlPressed();

	UFUNCTION()
		void OnVideoPressed();

	UFUNCTION()
		void OnBackPressed();


private:
	void ToggleEnableAndVisibility(bool isEnabled);

};
