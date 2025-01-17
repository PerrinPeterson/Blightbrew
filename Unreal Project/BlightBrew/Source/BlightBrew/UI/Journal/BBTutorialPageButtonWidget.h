// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBTutorialPageButtonWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBTutorialPageButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTitle(FString NewTitle);
	void SetPageSwitcher(class UWidgetSwitcher* NewPageSwitcher);
protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button;
	
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TitleText;

	FString Title;
	
	class UWidgetSwitcher* PageSwitcher;

	UFUNCTION()
		void OnButtonClicked();
	
};
