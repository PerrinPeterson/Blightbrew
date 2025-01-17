// Copyright © Too Many Eyes , 2022 - 2023


#include "BBCatalogWidget.h"
//Unreal Includes
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
//BlightBrew Includes
#include "Blightbrew/UI/Shop/BBCatalogEntryWidget.h"
#include "Blightbrew/UI/Inventory/BBDetailsPanel.h"


void UBBCatalogWidget::NativeConstruct()
{
	
}

void UBBCatalogWidget::RefreshCatalog(TMap<TSubclassOf<ABBBaseItem>, int64> itemCatalog)
{
	//Clear the old catalog
	CatalogEntries.Empty();
	CatalogScrollBox->ClearChildren();
	
	TArray<TSubclassOf<ABBBaseItem>> items;
	for (auto& item : itemCatalog)
	{
		items.Add(item.Key);
	}
	//Sorting the array alphebetically
	//items.Sort(&AlphebeticalSort);

	//Create catalog entries for each item
	for (auto& item : items)
	{
		UBBCatalogEntryWidget* CatalogEntry = CreateWidget<UBBCatalogEntryWidget>(GetWorld(), CatalogEntryClass);
		if (CatalogEntry)
		{
			CatalogEntry->SetItem(item);
			CatalogEntry->SetPrice(itemCatalog[item]);
			CatalogEntry->SetCatalogWidget(this);
			CatalogEntries.Add(CatalogEntry);
			CatalogScrollBox->AddChild(CatalogEntry);
		}
	}
}

void UBBCatalogWidget::SortCatalog()
{
	//Depricated
}

void UBBCatalogWidget::RefreshSelectedItemEntry()
{
	//Later Perrin Problem
}

bool UBBCatalogWidget::AlphebeticalSort(const TSubclassOf<class ABBBaseItem>& A, const TSubclassOf<class ABBBaseItem>& B)
{
	return A.GetDefaultObject()->GetItemName() < B.GetDefaultObject()->GetItemName();
}
