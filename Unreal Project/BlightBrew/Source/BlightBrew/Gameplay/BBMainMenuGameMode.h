// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BBMainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABBMainMenuGameMode();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		USoundMix* SoundMix;

	
};
