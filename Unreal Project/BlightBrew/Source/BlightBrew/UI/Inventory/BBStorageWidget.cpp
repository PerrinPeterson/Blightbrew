// Copyright © Too Many Eyes , 2022 - 2023


#include "BBStorageWidget.h"
#include "BBStorageInventoryWidget.h"
#include "../Crafting/BBCraftingInventoryWidget.h"
#include "../../Characters/Player/BBPlayerCharacter.h"
#include "../../Inventory/BBInventoryComponent.h"
#include "../BBMouseSlotWidget.h"
#include "BBDetailsPanel.h"

void UBBStorageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CraftingInventoryWidget->GetOwnerCharacter() == nullptr)
	{
		CraftingInventoryWidget->SetOwnerCharacter(OwningCharacter);
		StorageInventoryWidget->SetCraftingInventoryWidget(CraftingInventoryWidget);
	}
	if (MouseSlotWidget == nullptr)
	{
		MouseSlotWidget = CreateWidget<UBBMouseSlotWidget>(GetWorld(), MouseSlotClass);
		MouseSlotWidget->AddToViewport();
		MouseSlotWidget->SetOwnerCharacter(OwningCharacter);
		MouseSlotWidget->SetInventorySlot(OwningCharacter->GetInventoryComponent()->GetMouseSlot());
	}
	if (bIsEnabled && MouseSlotWidget->GetVisibility() != ESlateVisibility::HitTestInvisible)
	{
		MouseSlotWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UBBStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwningCharacter = Cast<ABBPlayerCharacter>(GetOwningPlayerPawn());

	CraftingInventoryWidget->SetOwnerCharacter(OwningCharacter);
	StorageInventoryWidget->SetCraftingInventoryWidget(CraftingInventoryWidget);
}

void UBBStorageWidget::Toggle(ABBStorageShelf* Shelf)
{
	bIsEnabled = !bIsEnabled;
	SetVisibility(bIsEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	OwningCharacter->SetIsInMenu(bIsEnabled);
	if (bIsEnabled)
	{
		StorageInventoryWidget->SetShelf(Shelf);
		CraftingInventoryWidget->SetOwnerCharacter(OwningCharacter);
		StorageInventoryWidget->SetCraftingInventoryWidget(CraftingInventoryWidget);
		CraftingInventoryWidget->SetDetailsPanel(CraftingDetailsWidget);
		CraftingDetailsWidget->ClearItem();
		StorageInventoryWidget->SetDetailsPanel(CraftingDetailsWidget);
	}
}

UBBMouseInventorySlotWidget* UBBStorageWidget::GetMouseSlot()
{
	return CraftingInventoryWidget->GetMouseSlot()->GetInventorySlot();
}
