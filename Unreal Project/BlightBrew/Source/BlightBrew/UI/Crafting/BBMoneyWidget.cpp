// Copyright © Too Many Eyes , 2022 - 2023


#include "BBMoneyWidget.h"
//Unreal Includes
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
//BlightBrew Includes
#include "../../Characters/Player/BBPlayerCharacter.h"

void UBBMoneyWidget::FadeOutWidget()
{
	//Slowly Fade the widget out, once its fully invisible, set the bWidgetVisible to false and set the widget to hidden
	float currentOpacity = GetRenderOpacity();
	if (currentOpacity > 0.0f)
	{
		SetRenderOpacity(currentOpacity - 0.01f);
	}
	else
	{
		bWidgetVisible = false;
		//SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBBMoneyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
	//Logic for when the player is in the game
	if (OwningPlayer != nullptr)
	{
		//If the money is different from the player's money, refresh the widget
		if (Money != OwningPlayer->GetCurrency())
		{
			bRefreshWidget = true;
		}
		if (bRefreshWidget)
		{
			bRefreshWidget = false;
			bWidgetVisible = true;
			//Set the timer for 5 seconds
			//If the player is in a menu, the timer shouldn't be set
			if (!OwningPlayer->IsInMenu())
				GetWorld()->GetTimerManager().SetTimer(timer, this, &UBBMoneyWidget::TriggerFadeOut, 5.0f, false);
			
			Money = OwningPlayer->GetCurrency();
			MoneyText->SetText(FText::FromString(FString::FromInt(Money)));
			SetRenderOpacity(1.0f);
			//SetVisibility(ESlateVisibility::Visible);
			bWidgetVisible = false; //To stop the widget from fading
		}
		if (bWidgetVisible)
		{
			//Fade out the widget
			FadeOutWidget();
		}
	}
}

void UBBMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
