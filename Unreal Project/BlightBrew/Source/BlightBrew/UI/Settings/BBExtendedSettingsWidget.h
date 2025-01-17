// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBExtendedSettingsWidget.generated.h"

class UBorder;
class UWidgetSwitcher;
class UButton;
class UTextBlock;
UENUM()
enum class EExtendedSettingsWidgetType
{
	Audio,
	Control,
	Video,
	Main,
};

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBExtendedSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchActiveWidget(EExtendedSettingsWidgetType widgetType);

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
	
};
