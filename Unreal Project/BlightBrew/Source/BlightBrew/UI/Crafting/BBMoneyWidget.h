// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBMoneyWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
		int32 Money = 0;
	
	void SetOwningPlayer(class ABBPlayerCharacter* owningPlayer) { OwningPlayer = owningPlayer; }
	void RefreshWidget() { bRefreshWidget = true; }
	void TriggerFadeOut() { bWidgetVisible = true; }
	void FadeOutWidget();

	
protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;
	
	//Player Reference
	UPROPERTY(VisibleAnywhere)
		class ABBPlayerCharacter* OwningPlayer;
	
	//Money Icon
	UPROPERTY(Meta = (BindWidget))
		class UImage* MoneyIcon;
	
	//Money Text
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MoneyText;
	
	bool bRefreshWidget = false;
	bool bWidgetVisible = false;
	FTimerHandle timer;
	
};