// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBAudioSettingsWidget.generated.h"

class USlider;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBAudioSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
		USoundMix* SoundMix;

	UPROPERTY(meta = (BindWidget))
		USlider* MasterVolumeSlider;

	UPROPERTY(EditDefaultsOnly)
		USoundClass* MasterSoundClass;

	UPROPERTY(meta = (BindWidget))
		USlider* MusicVolumeSlider;

	UPROPERTY(EditDefaultsOnly)
		USoundClass* MusicSoundClass;

	UPROPERTY(meta = (BindWidget))
		USlider* GameVolumeSlider;

	UPROPERTY(EditDefaultsOnly)
		USoundClass* GameSoundClass;


	//FAudioDeviceHandle AudioDevice;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnMasterSliderChanged(float Value);
	UFUNCTION()
		void OnMusicSliderChanged(float Value);
	UFUNCTION()
		void OnGameSliderChanged(float Value);

	UFUNCTION()
		void OnMasterVolumeChanged();
	UFUNCTION()
		void OnMusicVolumeChanged();
	UFUNCTION()
		void OnGameVolumeChanged();

	void UpdateSliders();

	void UpdateAudio(USoundClass* SoundClass);

	float MasterVolumePercent;
	float MusicVolumePercent;
	float GameVolumePercent;
	float DirtyValue;
	
};
