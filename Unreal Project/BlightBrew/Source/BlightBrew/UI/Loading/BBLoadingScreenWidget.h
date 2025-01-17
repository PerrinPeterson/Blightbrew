// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBLoadingScreenWidget.generated.h"

class UCircularThrobber;
class UThrobber;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBLoadingScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	float GetDelayTime() { return DelayTime; }

protected:
	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TipTextBlock;

	UPROPERTY(meta = (BindWidget))
		UCircularThrobber* Throbber;

	UPROPERTY(EditAnywhere)
		TArray<FText> TipTexts;

	UPROPERTY(EditAnywhere)
		float DelayTime;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;
	
};
