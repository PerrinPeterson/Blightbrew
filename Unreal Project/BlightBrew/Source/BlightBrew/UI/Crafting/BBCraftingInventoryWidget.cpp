// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Crafting/BBCraftingInventoryWidget.h"

#include "BlightBrew/Inventory/BBInventorySlotNew.h"
#include "BlightBrew/UI/BBMouseSlotWidget.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/UI/Inventory/BBInventorySlotWidget.h"
#include "Components/TextBlock.h"

void UBBCraftingInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	OwningCharacter = Cast<ABBPlayerCharacter>(GetOwningPlayerPawn());

	if (MouseSlot == nullptr)
	{
		MouseSlot = CreateWidget<UBBMouseSlotWidget>(GetWorld(), MouseSlotClass);
		MouseSlot->AddToViewport();
		MouseSlot->SetOwnerCharacter(OwningCharacter);
	}

	if (OwningCharacter && InventorySlot1->GetInventorySlot() == nullptr)
	{


		TArray<UBBInventorySlotNew*> InventorySlots = OwningCharacter->GetInventoryComponent()->GetInventorySlots();
		InventorySlot1->SetInventorySlot(InventorySlots[0]);
		InventorySlot2->SetInventorySlot(InventorySlots[1]);
		InventorySlot3->SetInventorySlot(InventorySlots[2]);
		InventorySlot4->SetInventorySlot(InventorySlots[3]);
		InventorySlot5->SetInventorySlot(InventorySlots[4]);
		InventorySlot6->SetInventorySlot(InventorySlots[5]);
		InventorySlot7->SetInventorySlot(InventorySlots[6]);
		InventorySlot8->SetInventorySlot(InventorySlots[7]);
		InventorySlot9->SetInventorySlot(InventorySlots[8]);
		InventorySlot10->SetInventorySlot(InventorySlots[9]);

		MouseSlot->SetInventorySlot(OwningCharacter->GetInventoryComponent()->GetMouseSlot());
	}

	if (DetailsPanel != nullptr && InventorySlot1->DetailsPanel == nullptr)
	{
		InventorySlot1->DetailsPanel = DetailsPanel;
		InventorySlot2->DetailsPanel = DetailsPanel;
		InventorySlot3->DetailsPanel = DetailsPanel;
		InventorySlot4->DetailsPanel = DetailsPanel;
		InventorySlot5->DetailsPanel = DetailsPanel;
		InventorySlot6->DetailsPanel = DetailsPanel;
		InventorySlot7->DetailsPanel = DetailsPanel;
		InventorySlot8->DetailsPanel = DetailsPanel;
		InventorySlot9->DetailsPanel = DetailsPanel;
		InventorySlot10->DetailsPanel = DetailsPanel;
	}

	if(Money->GetText().EqualTo(FText::FromString(FString::FromInt(OwningCharacter->GetCurrency()))))
		Money->SetText(FText::FromString(FString::FromInt(OwningCharacter->GetCurrency())));
	
}

void UBBCraftingInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlot1->SetCraftingInventoryWidget(this);
	InventorySlot2->SetCraftingInventoryWidget(this);
	InventorySlot3->SetCraftingInventoryWidget(this);
	InventorySlot4->SetCraftingInventoryWidget(this);
	InventorySlot5->SetCraftingInventoryWidget(this);
	InventorySlot6->SetCraftingInventoryWidget(this);
	InventorySlot7->SetCraftingInventoryWidget(this);
	InventorySlot8->SetCraftingInventoryWidget(this);
	InventorySlot9->SetCraftingInventoryWidget(this);
	InventorySlot10->SetCraftingInventoryWidget(this);

	InventorySlot1->DetailsPanel = DetailsPanel;
	InventorySlot2->DetailsPanel = DetailsPanel;
	InventorySlot3->DetailsPanel = DetailsPanel;
	InventorySlot4->DetailsPanel = DetailsPanel;
	InventorySlot5->DetailsPanel = DetailsPanel;
	InventorySlot6->DetailsPanel = DetailsPanel;
	InventorySlot7->DetailsPanel = DetailsPanel;
	InventorySlot8->DetailsPanel = DetailsPanel;
	InventorySlot9->DetailsPanel = DetailsPanel;
	InventorySlot10->DetailsPanel = DetailsPanel;
}
