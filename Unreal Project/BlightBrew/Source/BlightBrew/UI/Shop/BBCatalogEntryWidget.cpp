// Copyright © Too Many Eyes , 2022 - 2023


#include "BBCatalogEntryWidget.h"
//Unreal Includes
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
//BlightBrew Includes
#include "Blightbrew/Items/BBBaseItem.h"
#include "Blightbrew/UI/Inventory/BBDetailsPanel.h"
#include "Blightbrew/UI/Shop/BBCatalogWidget.h"


void UBBCatalogEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Button binding
	Button->OnClicked.AddDynamic(this, &UBBCatalogEntryWidget::OnButtonClicked);
}

void UBBCatalogEntryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
}

void UBBCatalogEntryWidget::OnButtonClicked()
{
	//Set the current item in the Catelog Widget
	CatalogWidget->SetSelectedItem(Item);
}

void UBBCatalogEntryWidget::SetItem(TSubclassOf<ABBBaseItem> InItem)
{
	Item = InItem;
	if (Item)
	{
		ItemImage->SetBrushFromTexture(Item.GetDefaultObject()->GetIcon());
		ItemNameText->SetText(FText::FromString(Item.GetDefaultObject()->GetItemName()));
	}

}

void UBBCatalogEntryWidget::SetPrice(int32 InPrice)
{
	PriceText->SetText(FText::FromString(FString::FromInt(InPrice)));
}

void UBBCatalogEntryWidget::SetCatalogWidget(UBBCatalogWidget* InCatalogWidget)
{
	CatalogWidget = InCatalogWidget;
}
