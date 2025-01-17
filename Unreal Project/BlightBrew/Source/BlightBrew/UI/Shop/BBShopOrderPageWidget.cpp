// Copyright © Too Many Eyes , 2022 - 2023


#include "BBShopOrderPageWidget.h"
//Unreal Includes
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
//BlightBrew Includes
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/UI/Shop/BBShopBookWidget.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/UI/Shop/BBCatalogWidget.h"
#include "BlightBrew/UI/Inventory/BBDetailsPanel.h"

void UBBShopOrderPageWidget::OnToggle()
{
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(0)));
}

void UBBShopOrderPageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Binds
	ExitButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnExitButtonPressed);
	ManagementPageButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnManagementPageButtonPressed);
	CatalogPageButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnCatalogPageButtonPressed);
	HistoryPageButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnHistoryPageButtonPressed);
	BuyButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnBuyButtonPressed);
	QuickAdjustPlusOneButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnQuickAdjustPlusOneButtonPressed);
	QuickAdjustPlusFiveButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnQuickAdjustPlusFiveButtonPressed);
	QuickAdjustMinusOneButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnQuickAdjustMinusOneButtonPressed);
	QuickAdjustMinusFiveButton->OnClicked.AddDynamic(this, &UBBShopOrderPageWidget::OnQuickAdjustMinusFiveButtonPressed);
	BuyAmountTextBox->OnTextChanged.AddDynamic(this, &UBBShopOrderPageWidget::OnTextChanged);

	//Set the text to 0
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(0)));

	if (CatalogWidget)
	{
		CatalogWidget->RefreshCatalog(ItemsForSale);
		SelectedItem = CatalogWidget->GetSelectedItem();
	}
}

void UBBShopOrderPageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (SelectedItem == nullptr)
		DetailsWidget->SetVisibility(ESlateVisibility::Hidden);
	if (SelectedItem != CatalogWidget->GetSelectedItem())
	{
		SelectedItem = CatalogWidget->GetSelectedItem();
		DetailsWidget->SetVisibility(ESlateVisibility::Visible);
		DetailsWidget->SetItem(SelectedItem.GetDefaultObject());
	}

	//Update Money Amount
	MoneyAmountText->SetText(FText::FromString(FString::FromInt(OwningCharacter->GetCurrency())));
	//If the amount is less than 0, set it to 0
	if (FCString::Atoi(*BuyAmountTextBox->GetText().ToString()) < 0)
		BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(0)));
	//If the cost of the selected amount is greater than the player's money, or the amount is 0, disable the buy button
	if (SelectedItem)
		if (FCString::Atoi(*BuyAmountTextBox->GetText().ToString()) * ItemsForSale[SelectedItem] > OwningCharacter->GetCurrency() || FCString::Atoi(*BuyAmountTextBox->GetText().ToString()) == 0)
		{
			BuyButton->SetIsEnabled(false);
		}
		else
		{
			BuyButton->SetIsEnabled(true);
		}
	else
		BuyButton->SetIsEnabled(false);

}

void UBBShopOrderPageWidget::OnBuyButtonPressed()
{
	//Convert the text to an int
	int64 Amount = FCString::Atoi(*BuyAmountTextBox->GetText().ToString());
	//If the amount is 0, do nothing
	if (Amount == 0)
		return;

	//If the amount is greater than 0, buy the item
	else
	{
		int64 cost = Amount * ItemsForSale[SelectedItem];
		if (cost <= OwningCharacter->GetCurrency())
		{
			OwningCharacter->GetInventoryComponent()->AddToInventory(SelectedItem.GetDefaultObject(), Amount);
			int Purchased = FCString::Atoi(*BuyAmountTextBox->GetText().ToString()) - Amount;
			cost = Purchased * ItemsForSale[SelectedItem];
			OwningCharacter->SetCurrency(OwningCharacter->GetCurrency() - cost);
		}
	}
}

void UBBShopOrderPageWidget::OnQuickAdjustPlusOneButtonPressed()
{
	int64 Amount = FCString::Atoi(*BuyAmountTextBox->GetText().ToString());
	Amount++;
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UBBShopOrderPageWidget::OnQuickAdjustPlusFiveButtonPressed()
{
	int64 Amount = FCString::Atoi(*BuyAmountTextBox->GetText().ToString());
	Amount += 5;
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UBBShopOrderPageWidget::OnQuickAdjustMinusOneButtonPressed()
{
	int64 Amount = FCString::Atoi(*BuyAmountTextBox->GetText().ToString());
	Amount--;
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UBBShopOrderPageWidget::OnQuickAdjustMinusFiveButtonPressed()
{
	int64 Amount = FCString::Atoi(*BuyAmountTextBox->GetText().ToString());
	Amount -= 5;
	BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UBBShopOrderPageWidget::OnExitButtonPressed()
{
	if (OwningBookWidget)
	{
		if (OwningCharacter)
			OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
		OwningBookWidget->Toggle();
	}
}

void UBBShopOrderPageWidget::OnManagementPageButtonPressed()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_MANAGEMENT);
	}
}

void UBBShopOrderPageWidget::OnCatalogPageButtonPressed()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_CATALOGUE);
	}
}

void UBBShopOrderPageWidget::OnHistoryPageButtonPressed()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_HISTORY);
	}
}

void UBBShopOrderPageWidget::OnTextChanged(const FText& Text)
{
	//Ensure that the textbox only has numbers, and no decimals, but can be empty
	if (Text.ToString().Contains(".") || Text.ToString().Contains(",") || Text.ToString().Contains(" ") || Text.ToString().Contains("-") || Text.ToString().Contains("e"))
		BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(LastEnteredNumber)));
	if (BuyAmountTextBox->GetText().IsNumeric())
	{
		LastEnteredNumber = FCString::Atoi(*Text.ToString());
		BuyAmountTextBox->SetText(FText::FromString(FString::FromInt(LastEnteredNumber)));
	}
	//LastEnteredNumber = FCString::Atoi(*Text.ToString());
}
