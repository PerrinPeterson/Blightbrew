// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlightBrewGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABlightBrewGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlightBrewGameModeBase();

	UFUNCTION(Exec, Category = ExecFunctions)
		void Debug(FString Command);

	UFUNCTION(Exec, Category = ExecFunctions)
		void DilateTime(float amount);

	UFUNCTION(Exec, Category = ExecFunctions)
		void Unstuck();
};
