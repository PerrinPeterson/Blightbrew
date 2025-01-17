// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Gameplay/BBMainMenuGameMode.h"

#include "GameFramework/GameUserSettings.h"
#include "AudioDevice.h"

ABBMainMenuGameMode::ABBMainMenuGameMode()
{

}

void ABBMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(SoundMix != nullptr)
	{
		GetGameInstance()->GetEngine()->GetMainAudioDevice()->SetBaseSoundMix(SoundMix);
	}
	
	UGameUserSettings* UserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();
	UserSettings->RunHardwareBenchmark();
	UserSettings->ApplyHardwareBenchmarkResults();

}
