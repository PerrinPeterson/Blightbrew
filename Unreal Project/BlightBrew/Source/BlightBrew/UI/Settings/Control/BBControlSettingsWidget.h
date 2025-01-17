// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBControlSettingsWidget.generated.h"

class UCheckBox;
class USlider;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBControlSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:


	UPROPERTY(meta = (BindWidget))
		USlider* MouseXSlider;

	UPROPERTY(meta = (BindWidget))
		USlider* MouseYSlider;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* InvertYCheckBox;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnMouseXChanged(float Value);
	UFUNCTION()
		void OnMouseYChanged(float Value);
	UFUNCTION()
		void OnInvertYChanged(bool state);
	
};
