// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Settings/Audio/BBAudioSettingsWidget.h"

#include "AudioDevice.h"
#include "Components/Slider.h"
#include "Sound/SoundMix.h"

void UBBAudioSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);



}

void UBBAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice();

	//AudioDevice->SetBaseSoundMix(SoundMix);


	GetGameInstance()->GetEngine()->GetMainAudioDevice()->RegisterSoundClass(MasterSoundClass);
	GetGameInstance()->GetEngine()->GetMainAudioDevice()->RegisterSoundClass(MusicSoundClass);
	GetGameInstance()->GetEngine()->GetMainAudioDevice()->RegisterSoundClass(GameSoundClass);

	GetGameInstance()->GetEngine()->GetMainAudioDevice()->SetBaseSoundMix(SoundMix);

	MasterVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UBBAudioSettingsWidget::OnMasterVolumeChanged);
	MusicVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UBBAudioSettingsWidget::OnMusicVolumeChanged);
	GameVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UBBAudioSettingsWidget::OnGameVolumeChanged);

	MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UBBAudioSettingsWidget::OnMasterSliderChanged);
	MusicVolumeSlider->OnValueChanged.AddDynamic(this, &UBBAudioSettingsWidget::OnMusicSliderChanged);
	GameVolumeSlider->OnValueChanged.AddDynamic(this, &UBBAudioSettingsWidget::OnGameSliderChanged);



	//UpdateSliders();

}

void UBBAudioSettingsWidget::OnMasterSliderChanged(float Value)
{
	DirtyValue = Value;
}

void UBBAudioSettingsWidget::OnMusicSliderChanged(float Value)
{
	DirtyValue = Value;
}

void UBBAudioSettingsWidget::OnGameSliderChanged(float Value)
{
	DirtyValue = Value;
}

void UBBAudioSettingsWidget::OnMasterVolumeChanged()
{
	//float value = MasterVolumeSlider->GetValue();
	//GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice()->SetSoundMixClassOverride(SoundMix, MasterSoundClass, value, 1, 1, true);

	UpdateAudio(MasterSoundClass);

	UpdateSliders();
}

void UBBAudioSettingsWidget::OnMusicVolumeChanged()
{
	//float value = MusicVolumeSlider->GetValue();
	//GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice()->SetSoundMixClassOverride(SoundMix, MusicSoundClass, value, 1, 1, true);

	UpdateAudio(MusicSoundClass);
	UpdateSliders();
}

void UBBAudioSettingsWidget::OnGameVolumeChanged()
{
	//float value = GameVolumeSlider->GetValue();
	//GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice()->SetSoundMixClassOverride(SoundMix, GameSoundClass, value, 1, 1, true);
	UpdateAudio(GameSoundClass);
	UpdateSliders();
}

void UBBAudioSettingsWidget::UpdateSliders()
{
	//if (AudioDevice)
	if (FAudioDevice* AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice())
	{
		//FAudioDevice* AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice();

		if (AudioDevice)
		{
			FAudioThread::RunCommandOnAudioThread([this, AudioDevice]()
				{
					if (AudioDevice)
					{
						//code that will run in audio thread
						MasterVolumePercent = AudioDevice->GetSoundClassCurrentProperties(MasterSoundClass)->Volume;
						MusicVolumePercent = AudioDevice->GetSoundClassCurrentProperties(MusicSoundClass)->Volume;
						GameVolumePercent = AudioDevice->GetSoundClassCurrentProperties(GameSoundClass)->Volume;
					}

				});
		}




		MasterVolumeSlider->SetValue(MasterVolumePercent);
		MusicVolumeSlider->SetValue(MusicVolumePercent);
		GameVolumeSlider->SetValue(GameVolumePercent);
	}
}

void UBBAudioSettingsWidget::UpdateAudio(USoundClass* SoundClass)
{
	if(SoundClass == MasterSoundClass)
	{
		if (FAudioDevice* AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice())
		{
			if (AudioDevice)
			{
				FAudioThread::RunCommandOnAudioThread([this, AudioDevice]()
					{
						if (AudioDevice)
						{
							//code that will run in audio thread
							AudioDevice->SetSoundMixClassOverride(SoundMix, MasterSoundClass, DirtyValue, 1, 1, true);
						}

					});
			}

		}
	}
	if (SoundClass == MusicSoundClass)
	{
		if (FAudioDevice* AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice())
		{
			if (AudioDevice)
			{
				FAudioThread::RunCommandOnAudioThread([this, AudioDevice]()
					{
						if (AudioDevice)
						{
							//code that will run in audio thread
							AudioDevice->SetSoundMixClassOverride(SoundMix, MusicSoundClass, DirtyValue, 1, 1, true);
						}

					});
			}

		}
	}
	if (SoundClass == GameSoundClass)
	{
		if (FAudioDevice* AudioDevice = GetGameInstance()->GetEngine()->GetMainAudioDevice().GetAudioDevice())
		{
			if (AudioDevice)
			{
				FAudioThread::RunCommandOnAudioThread([this, AudioDevice]()
					{
						if (AudioDevice)
						{
							//code that will run in audio thread
							AudioDevice->SetSoundMixClassOverride(SoundMix, GameSoundClass, DirtyValue, 1, 1, true);
						}

					});
			}

		}
	}


}
