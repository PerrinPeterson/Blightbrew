// Copyright © Too Many Eyes , 2022 - 2023


#include "BBStorageInventoryWidget.h"
#include "../../Characters/Player/BBPlayerCharacter.h"
#include "BBInventorySlotWidget.h"
#include "../../Inventory/Storage/BBStorageShelf.h"

void UBBStorageInventoryWidget::SetShelf(ABBStorageShelf* InShelf)
{
	Shelf = InShelf;
	if (Shelf != nullptr)
	{
		TArray<UBBInventorySlotNew*> InventorySlots = Shelf->GetStorageSlots();
		InventorySlot1->SetInventorySlot(InventorySlots[0]);
		InventorySlot2->SetInventorySlot(InventorySlots[1]);
		InventorySlot3->SetInventorySlot(InventorySlots[2]);
		InventorySlot4->SetInventorySlot(InventorySlots[3]);
		InventorySlot5->SetInventorySlot(InventorySlots[4]);
		InventorySlot6->SetInventorySlot(InventorySlots[5]);
	}
}

void UBBStorageInventoryWidget::SetCraftingInventoryWidget(UBBCraftingInventoryWidget* inWidget)
{
	CraftingInventoryWidget = inWidget;
	InventorySlot1->SetCraftingInventoryWidget(inWidget);
	InventorySlot2->SetCraftingInventoryWidget(inWidget);
	InventorySlot3->SetCraftingInventoryWidget(inWidget);
	InventorySlot4->SetCraftingInventoryWidget(inWidget);
	InventorySlot5->SetCraftingInventoryWidget(inWidget);
	InventorySlot6->SetCraftingInventoryWidget(inWidget);
}

void UBBStorageInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (DetailsPanel != nullptr && InventorySlot1->DetailsPanel == nullptr)
	{
		InventorySlot1->DetailsPanel = DetailsPanel;
		InventorySlot2->DetailsPanel = DetailsPanel;
		InventorySlot3->DetailsPanel = DetailsPanel;
		InventorySlot4->DetailsPanel = DetailsPanel;
		InventorySlot5->DetailsPanel = DetailsPanel;
		InventorySlot6->DetailsPanel = DetailsPanel;
	}
}

void UBBStorageInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InventorySlot1->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot2->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot3->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot4->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot5->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot6->SetCraftingInventoryWidget(CraftingInventoryWidget);

	InventorySlot1->DetailsPanel = DetailsPanel;
	InventorySlot2->DetailsPanel = DetailsPanel;
	InventorySlot3->DetailsPanel = DetailsPanel;
	InventorySlot4->DetailsPanel = DetailsPanel;
	InventorySlot5->DetailsPanel = DetailsPanel;
	InventorySlot6->DetailsPanel = DetailsPanel;
}
