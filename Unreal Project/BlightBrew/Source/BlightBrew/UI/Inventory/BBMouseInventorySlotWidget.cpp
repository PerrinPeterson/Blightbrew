// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Inventory/BBMouseInventorySlotWidget.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Items/BBBaseItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "BlightBrew/Inventory/BBInventorySlotNew.h"

bool UBBMouseInventorySlotWidget::SetInventorySlot(UBBInventorySlotNew* InInventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse Slot Allocating..."));
	if (InInventorySlot != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Mouse Slot Allocated."));
		InventorySlot = InInventorySlot;
		return true;
	}
	return false;
}

void UBBMouseInventorySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (InventorySlot != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Slot Valid"));
		if (InventorySlot->GetItem() != nullptr
			&& OwningCharacter->IsInMenu())
		{
			bIsHidden = false;
			//UE_LOG(LogTemp, Warning, TEXT("Item Valid"));
			float quantity = InventorySlot->GetStackSize();

			if (quantity > 1)
			{
				//Quantity->Text = FText::AsNumber(quantity);
				Quantity->SetText(FText::AsNumber(quantity));
				Quantity->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				Quantity->SetVisibility(ESlateVisibility::Hidden);
			}
			Icon->SetVisibility(ESlateVisibility::Visible);
			Icon->SetBrushFromTexture(InventorySlot->GetItem()->GetIcon());

		}
		else if (!bIsHidden)
		{
			bIsHidden = true;
			Icon->SetVisibility(ESlateVisibility::Hidden);
			Quantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void UBBMouseInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Icon->

	Quantity->SetVisibility(ESlateVisibility::Hidden);
	Icon->SetVisibility(ESlateVisibility::Hidden);
	bIsHidden = true;
}
