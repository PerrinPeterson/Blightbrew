// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBCreditsMenuWidget.generated.h"

class UWidgetSwitcher;
class UButton;
class UTextBlock;
class UBorder;

UENUM()
enum class ECreditWidgetType
{
	Art,
	Audio,
	Design,
	Environment,
	Programming,
	UI,
};

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBCreditsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;


	UFUNCTION()
		void OnBack();


	void NativeConstruct() override;
	
};
