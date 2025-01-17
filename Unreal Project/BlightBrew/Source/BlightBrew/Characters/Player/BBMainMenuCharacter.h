// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/BBCharacterBase.h"
#include "BBMainMenuCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBMainMenuCharacter : public ABBCharacterBase
{
	GENERATED_BODY()

public:
	ABBMainMenuCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
		class UBBMainMenuParentWidget* MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
		class TSubclassOf<UBBMainMenuParentWidget> MainMenuClass;

protected:
	virtual void BeginPlay() override;
};
