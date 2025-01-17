// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBVideoSettingsWidget.generated.h"

class USlider;
class UButton;
class UTextBlock;
class UScrollBox;
class UBorder;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBVideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;


	UPROPERTY(meta = (BindWidget))
		UScrollBox* ScrollBox;

#pragma region WindowMode
	UPROPERTY(meta = (BindWidget))
		UTextBlock* WindowModeTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* WindowModeButtonL;

	UFUNCTION()
		void OnWindowLeft();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* WindowModeTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* WindowModeButtonR;

	UFUNCTION()
		void OnWindowRight();

	int WindowModeCounter;

	void UpdateWindowMode();

#pragma endregion WindowMode

#pragma region Resolution
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ResolutionTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* ResolutionButtonL;

	UFUNCTION()
		void OnResolutionLeft();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ResolutionTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* ResolutionButtonR;

	UFUNCTION()
		void OnResolutionRight();

	void UpdateResolution();

	int ResolutionCounter;

#pragma endregion Resolution

#pragma region ShadowQuality

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ShadowQTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* ShadowQButtonL;

	UFUNCTION()
		void OnShadowLeft();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ShadowQTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* ShadowQButtonR;

	UFUNCTION()
		void OnShadowRight();

	int ShadowCounter;

	void UpdateShadow();

#pragma endregion ShadowQuality

#pragma region TextureQuality

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextureQTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* TextureQButtonL;

	UFUNCTION()
		void OnTextureLeft();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextureQTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* TextureQButtonR;

	UFUNCTION()
		void OnTextureRight();

	int TextureCounter;

	void UpdateTexture();

#pragma endregion TextureQuality

#pragma region FoliageQuality

	UPROPERTY(meta = (BindWidget))
		UTextBlock* FoliageQTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* FoliageQButtonL;

	UFUNCTION()
		void OnFoliageLeft();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* FoliageQTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* FoliageQButtonR;

	UFUNCTION()
		void OnFoliageRight();

	int FoliageCounter;

	void UpdateFoliage();

#pragma endregion FoliageQuality

#pragma region VSync

	UPROPERTY(meta = (BindWidget))
		UTextBlock* VSyncTitleTextBox;

	UPROPERTY(meta = (BindWidget))
		UButton* VSyncCheckBox;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* VSyncToggleText;

	UFUNCTION()
		void OnVSyncPressed();

	bool bIsVSyncEnabled;

#pragma endregion VSync

#pragma region Brightness
	UPROPERTY(meta = (BindWidget))
		USlider* BrightnessSlider;

	float BrightnessValue;

	UFUNCTION()
		void OnBrightnessChanged(float Value);
#pragma endregion Brightness

	UPROPERTY(meta = (BindWidget))
		UButton* ApplyButton;

	UFUNCTION()
		void Apply();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

private:
	UGameUserSettings* UserSettings;


	
};
