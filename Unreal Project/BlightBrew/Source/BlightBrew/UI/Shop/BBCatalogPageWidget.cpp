// Copyright © Too Many Eyes , 2022 - 2023


#include "BBCatalogPageWidget.h"
//Unreal Includes
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/EditableText.h"
#include "SlateCore/Public/Input/Reply.h"
//BlightBrew Includes
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/UI/Shop/BBShopBookWidget.h"
#include "BlightBrew/UI/Shop/BBCatalogWidget.h"
#include "BlightBrew/Shop/BBShopBook.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/Inventory/BBDetailsPanel.h"


void UBBCatalogPageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Binds
	ExitButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::ExitButtonClicked);
	ManagementPageButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::ManagementPageButtonClicked);
	OrderPageButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::OrderPageButtonClicked);
	HistoryPageButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::HistoryPageButtonClicked);
	QuickAdjustPlusOneButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::QuickAdjustPlusOneButtonClicked);
	QuickAdjustPlusFiveButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::QuickAdjustPlusFiveButtonClicked);
	QuickAdjustMinusOneButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::QuickAdjustMinusOneButtonClicked);
	QuickAdjustMinusFiveButton->OnClicked.AddDynamic(this, &UBBCatalogPageWidget::QuickAdjustMinusFiveButtonClicked);
	CustomPriceTextBox->OnTextCommitted.AddDynamic(this, &UBBCatalogPageWidget::CustomPriceTextBoxChanged);
	CustomPriceTextBox->OnTextChanged.AddDynamic(this, &UBBCatalogPageWidget::OnTextChanged);

	//Create the catalogue entries
	if (OwningBookWidget)
	{
		TMap<TSubclassOf<ABBBaseItem>, int64> itemCatalog = OwningBookWidget->GetOwningBook()->Shop->GetItemCatalog();
		CatalogueWidget->RefreshCatalog(itemCatalog);
	}
	
}

void UBBCatalogPageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//See if the details panel has an Item in it, if not, hide the price, and adjustment buttons.
	CurrentSelectedItem = CatalogueWidget->GetSelectedItem();
	
	if (CurrentSelectedItem != nullptr)
	{
		
		if (CurrentSelectedItem.GetDefaultObject()->GetItemName() != DetailsPanel->GetItemName())
		{
			DetailsPanel->SetItem(CurrentSelectedItem.GetDefaultObject());
			CustomPriceTextBox->SetVisibility(ESlateVisibility::Visible);
			QuickAdjustPlusOneButton->SetVisibility(ESlateVisibility::Visible);
			QuickAdjustPlusFiveButton->SetVisibility(ESlateVisibility::Visible);
			QuickAdjustMinusOneButton->SetVisibility(ESlateVisibility::Visible);
			QuickAdjustMinusFiveButton->SetVisibility(ESlateVisibility::Visible);
			DetailsPanel->SetVisibility(ESlateVisibility::Visible);
			int64 price = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
			FString priceString = FString::FromInt(price);
			FText priceText = FText::FromString(priceString);
			CustomPriceTextBox->SetText(priceText);
		}
		//Set the price text
		/*int64 price = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
		FString priceString = FString::FromInt(price);
		FText priceText = FText::FromString(priceString);
		CustomPriceTextBox->SetText(priceText);*/
		//TODO: Set up a way to set the price in the CatalogWidget of a specific item.
	}
	else
	{
		CustomPriceTextBox->SetVisibility(ESlateVisibility::Hidden);
		QuickAdjustPlusOneButton->SetVisibility(ESlateVisibility::Hidden);
		QuickAdjustPlusFiveButton->SetVisibility(ESlateVisibility::Hidden);
		QuickAdjustMinusOneButton->SetVisibility(ESlateVisibility::Hidden);
		QuickAdjustMinusFiveButton->SetVisibility(ESlateVisibility::Hidden);
		DetailsPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBBCatalogPageWidget::SetCurrentlySelectedItem(TSubclassOf<class ABBBaseItem> itemClass)
{
	if (itemClass)
	{
		CurrentSelectedItem = itemClass;
	}
}

void UBBCatalogPageWidget::ExitButtonClicked()
{
	if (OwningBookWidget)
	{
		if (OwningCharacter)
			OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
		OwningBookWidget->Toggle();
	}
}

void UBBCatalogPageWidget::ManagementPageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_MANAGEMENT);
	}
}

void UBBCatalogPageWidget::OrderPageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_ORDER);
	}
}

void UBBCatalogPageWidget::HistoryPageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_HISTORY);
	}
}

void UBBCatalogPageWidget::QuickAdjustPlusOneButtonClicked()
{
	//Grab the old price
	int64 oldPrice = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
	//Subtract 5 from the old price
	int64 newPrice = oldPrice + 1;
	//Set the new price
	OwningBookWidget->GetOwningBook()->Shop->SetShopItemValue(CurrentSelectedItem, newPrice);
	//Set the text box to the new price
	FString priceString = FString::FromInt(newPrice);
	FText priceText = FText::FromString(priceString);
	CustomPriceTextBox->SetText(priceText);
	RefreshCatalogue();
}

void UBBCatalogPageWidget::QuickAdjustPlusFiveButtonClicked()
{
	//Grab the old price
	int64 oldPrice = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
	//Add 5 to the old price
	int64 newPrice = oldPrice + 5;
	//Set the new price
	OwningBookWidget->GetOwningBook()->Shop->SetShopItemValue(CurrentSelectedItem, newPrice);
	//Set the text box to the new price
	FString priceString = FString::FromInt(newPrice);
	FText priceText = FText::FromString(priceString);
	CustomPriceTextBox->SetText(priceText);
	RefreshCatalogue();
}

void UBBCatalogPageWidget::QuickAdjustMinusOneButtonClicked()
{
	//Grab the old price
	int64 oldPrice = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
	//Subtract 5 from the old price
	int64 newPrice = oldPrice - 1;
	//Set the new price
	OwningBookWidget->GetOwningBook()->Shop->SetShopItemValue(CurrentSelectedItem, newPrice);
	//Set the text box to the new price
	FString priceString = FString::FromInt(newPrice);
	FText priceText = FText::FromString(priceString);
	CustomPriceTextBox->SetText(priceText);
	RefreshCatalogue();
}

void UBBCatalogPageWidget::QuickAdjustMinusFiveButtonClicked()
{
	//Grab the old price
	int64 oldPrice = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
	//Subtract 5 from the old price
	int64 newPrice = oldPrice - 5;
	//Set the new price
	OwningBookWidget->GetOwningBook()->Shop->SetShopItemValue(CurrentSelectedItem, newPrice);
	//Set the text box to the new price
	FString priceString = FString::FromInt(newPrice);
	FText priceText = FText::FromString(priceString);
	CustomPriceTextBox->SetText(priceText);
	RefreshCatalogue();
}

void UBBCatalogPageWidget::CustomPriceTextBoxChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	//Check if the text is a number
	RefreshCatalogue();
}

void UBBCatalogPageWidget::OnTextChanged(const FText& Text)
{
	if (Text.ToString().Contains(".") || Text.ToString().Contains(",") || Text.ToString().Contains(" ") || Text.ToString().Contains("-") || Text.ToString().Contains("e"))
		CustomPriceTextBox->SetText(FText::FromString(FString::FromInt(LastEnteredNumber)));
	if (CustomPriceTextBox->GetText().IsNumeric())
	{
		LastEnteredNumber = FCString::Atoi(*Text.ToString());
		CustomPriceTextBox->SetText(FText::FromString(FString::FromInt(LastEnteredNumber)));
	}
	OwningBookWidget->GetOwningBook()->Shop->SetShopItemValue(CurrentSelectedItem, LastEnteredNumber);
}

void UBBCatalogPageWidget::RefreshCatalogue()
{
	TMap<TSubclassOf<ABBBaseItem>, int64> itemCatalog = OwningBookWidget->GetOwningBook()->Shop->GetItemCatalog();
	CatalogueWidget->RefreshCatalog(itemCatalog);
	SortCatalogue();
}

void UBBCatalogPageWidget::SortCatalogue()
{
	CatalogueWidget->SortCatalog();
}

void UBBCatalogPageWidget::OnToggle()
{
	int64 price = OwningBookWidget->GetOwningBook()->Shop->GetShopItemValue(CurrentSelectedItem);
	FString priceString = FString::FromInt(price);
	FText priceText = FText::FromString(priceString);
	CustomPriceTextBox->SetText(priceText);
}
