// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBTutorialPageWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBTutorialPageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew")
		FString Title;

};
