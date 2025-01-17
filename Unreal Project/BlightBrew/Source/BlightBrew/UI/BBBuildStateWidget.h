// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBBuildStateWidget.generated.h"

class UBorder;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBBuildStateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* BuildTextBlock;
	
};
