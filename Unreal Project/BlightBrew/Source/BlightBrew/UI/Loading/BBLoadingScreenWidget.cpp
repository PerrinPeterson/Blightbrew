// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Loading/BBLoadingScreenWidget.h"

#include "Components/TextBlock.h"

void UBBLoadingScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBBLoadingScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();


	if(TipTexts.Num() > 0)
	{
		int index = FMath::RandRange(0, TipTexts.Num() - 1);

		TipTextBlock->SetText(TipTexts[index]);
	}
	else
	{
		TipTextBlock->SetText(FText::FromString("Etiam Multis Oculis"));
	}
}
