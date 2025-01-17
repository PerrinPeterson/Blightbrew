// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Inventory/BBQuickSlotWidget.h"

#include "BBInventorySlotWidget.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"

void UBBQuickSlotWidget::DisableQuickslotButtons()
{
	QuickSlotWidget1->DisableButton();
	QuickSlotWidget2->DisableButton();
	QuickSlotWidget3->DisableButton();
}

void UBBQuickSlotWidget::EnableQuickslotButtons()
{
	QuickSlotWidget1->EnableButton();
	QuickSlotWidget2->EnableButton();
	QuickSlotWidget3->EnableButton();
}

void UBBQuickSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBBQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(OwningCharacter)
	{
		TArray<UBBInventorySlotNew*> QuickSlots = OwningCharacter->GetInventoryComponent()->GetQuickSlots();

		QuickSlotWidget1->SetInventorySlot(QuickSlots[0]);
		QuickSlotWidget2->SetInventorySlot(QuickSlots[1]);
		QuickSlotWidget3->SetInventorySlot(QuickSlots[2]);
	}
}
