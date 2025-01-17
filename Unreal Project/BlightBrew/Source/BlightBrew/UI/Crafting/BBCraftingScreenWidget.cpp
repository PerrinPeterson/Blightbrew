// Copyright © Too Many Eyes , 2022


#include "BBCraftingScreenWidget.h"
#include "BBCraftingWidget.h"
#include "Components/Button.h"
#include "../../Inventory/BBInventorySlotNew.h"
#include "../Inventory/BBInventorySlotWidget.h"

void UBBCraftingScreenWidget::OnCraft()
{
	craftingStation->Craft();
}

void UBBCraftingScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!bHasAllocated)
	{
		InventorySlot1->SetCraftingInventoryWidget(CraftingInventoryWidget);
		InventorySlot2->SetCraftingInventoryWidget(CraftingInventoryWidget);
		InventorySlot3->SetCraftingInventoryWidget(CraftingInventoryWidget);
		OutputSlot->SetCraftingInventoryWidget(CraftingInventoryWidget);

		if (craftingStation != nullptr)
		{
			InventorySlot1->SetInventorySlot(craftingStation->CraftingSlots[0]);
			InventorySlot2->SetInventorySlot(craftingStation->CraftingSlots[1]);
			InventorySlot3->SetInventorySlot(craftingStation->CraftingSlots[2]);
			OutputSlot->SetInventorySlot(craftingStation->ProductSlot);
		}
		if (InventorySlot1->DetailsPanel == nullptr && DetailsPanel != nullptr)
		{
			InventorySlot1->DetailsPanel = DetailsPanel;
			InventorySlot2->DetailsPanel = DetailsPanel;
			InventorySlot3->DetailsPanel = DetailsPanel;
			OutputSlot->DetailsPanel = DetailsPanel;
		}
		if (InventorySlot1->GetCraftingInventoryWidget() != nullptr
			&& InventorySlot1->GetInventorySlot() != nullptr
			&& InventorySlot1->DetailsPanel != nullptr)
			bHasAllocated = true;
	}
	
}

void UBBCraftingScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlot1->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot2->SetCraftingInventoryWidget(CraftingInventoryWidget);
	InventorySlot3->SetCraftingInventoryWidget(CraftingInventoryWidget);
	OutputSlot->SetCraftingInventoryWidget(CraftingInventoryWidget);
	
	/*slot1 = NewObject<UBBInventorySlotNew>();
	slot2 = NewObject<UBBInventorySlotNew>();
	slot3 = NewObject<UBBInventorySlotNew>();
	slotOut = NewObject<UBBInventorySlotNew>();*/
	

	/*InventorySlot1->SetInventorySlot(craftingStation->CraftingSlots[0]);
	InventorySlot2->SetInventorySlot(craftingStation->CraftingSlots[1]);
	InventorySlot3->SetInventorySlot(craftingStation->CraftingSlots[2]);
	OutputSlot->SetInventorySlot(craftingStation->ProductSlot);*/

	Craft->OnPressed.AddDynamic(this, &UBBCraftingScreenWidget::OnCraft);

	InventorySlot1->DetailsPanel = DetailsPanel;
	InventorySlot2->DetailsPanel = DetailsPanel;
	InventorySlot3->DetailsPanel = DetailsPanel;
	OutputSlot->DetailsPanel = DetailsPanel;
}
