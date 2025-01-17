// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/BBFocusTextWidget.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "Components/TextBlock.h"

void UBBFocusTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(OwningCharacter->IsFocusing())
	{
		FocusTextBlock->SetText(OwningCharacter->GetFocusText());
	}
	else
	{
		FocusTextBlock->SetText(FText::FromString(""));
	}
	
}

void UBBFocusTextWidget::NativeConstruct()
{
	Super::NativeConstruct();


}
