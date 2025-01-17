// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBTimeWidget.generated.h"

class UImage;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBTimeWidget : public UUserWidget
{
	GENERATED_BODY()

//public:

protected:

	UPROPERTY(meta = (BindWidget))
		UProgressBar* TimeBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentHourTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentMinuteTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TimeOfDayTextBlock;


		float CurrentSeconds;
		float CurrentMinutes;
		float CurrentHours;

		float TotalMinutes;

	UPROPERTY(meta = (BindWidget))
		UImage* FlairImage1;

	UPROPERTY(meta = (BindWidget))
		UImage* FlairImage2;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
