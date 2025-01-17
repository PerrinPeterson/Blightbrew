// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Inventory/BBInventorySlotWidget.h"
//Unreal Includes
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
//Blightbrew Includes
#include "BBDetailsPanel.h"
#include "BBInventoryWidget.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/Items/BBBaseItem.h"
#include "BlightBrew/UI/BBMouseSlotWidget.h"
#include "../Crafting/BBCraftingInventoryWidget.h"
#include "../../Inventory/BBInventorySlotNew.h"

bool UBBInventorySlotWidget::SetInventorySlot(UBBInventorySlotNew* InInventorySlot)
{
	////UE_LOG(LogTemp, Warning, TEXT("Slot Allocating..."));
	if (InInventorySlot != nullptr)
	{
		////UE_LOG(LogTemp, Warning, TEXT("Slot Allocated."));
		InventorySlot = InInventorySlot;
		return true;
	}
	else
	{
		////UE_LOG(LogTemp, Warning, TEXT("Slot Not Allocated. [Slot Null]"));
		return false;
	}
}

void UBBInventorySlotWidget::ShowName()
{
	//Show the nameplate
	TArray<UWidget*> widgets;
	widgets = ItemNamePlate->GetAllChildren();
	for (int i = 0; i < widgets.Num(); i++)
	{
		if (widgets[i]->GetName() == "ItemName")
		{
			UTextBlock* text = Cast<UTextBlock>(widgets[i]);
			text->SetText(FText::FromString(InventorySlot->GetItem()->GetItemName()));
		}
	}
	ItemNamePlate->SetVisibility(ESlateVisibility::Visible);
}

void UBBInventorySlotWidget::DisableButton()
{
	Button->bIsEnabled = false;
}

void UBBInventorySlotWidget::EnableButton()
{
	Button->bIsEnabled = true;
}

void UBBInventorySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	Super::NativeTick(MyGeometry, InDeltaTime);
	if (InventorySlot != nullptr)
	{
		////UE_LOG(LogTemp, Warning, TEXT("Slot Valid"));
		if (InventorySlot->GetItem() != nullptr)
		{
			////UE_LOG(LogTemp, Warning, TEXT("Item Valid"));
			float quantity = InventorySlot->GetStackSize();
			SlotBackground->SetOpacity(1.0f);
			Button->SetToolTipText(FText::FromString(InventorySlot->GetItemName()));

			if (quantity > 1)
			{
				//Quantity->Text = FText::AsNumber(quantity);
				Quantity->SetText(FText::AsNumber(quantity));
				Quantity->SetVisibility(ESlateVisibility::Visible);
				ItemQuantityAmount->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				Quantity->SetVisibility(ESlateVisibility::Hidden);
				ItemQuantityAmount->SetVisibility(ESlateVisibility::Hidden);
			}

			if (InventorySlot->IsSelected())
			{
				Outline->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				Outline->SetVisibility(ESlateVisibility::Hidden);
			}
			Icon->SetVisibility(ESlateVisibility::Visible);
			Icon->SetBrushFromTexture(InventorySlot->GetItem()->GetIcon());

		}
		else
		{
			Icon->SetVisibility(ESlateVisibility::Hidden);
			Quantity->SetVisibility(ESlateVisibility::Hidden);
			ItemQuantityAmount->SetVisibility(ESlateVisibility::Hidden);
			SlotBackground->SetOpacity(0.5f);
			Button->SetToolTipText(FText::FromString(""));
		}
	}

}

void UBBInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Icon->SetVisibility(ESlateVisibility::Hidden);
	Outline->SetVisibility(ESlateVisibility::Hidden);
	Quantity->SetVisibility(ESlateVisibility::Hidden);
	//Set the Children of the NamePlate to be hidden
	ItemNamePlate->SetVisibility(ESlateVisibility::Hidden);


	Button->OnPressed.AddDynamic(this, &UBBInventorySlotWidget::OnClick);
	//Added a hover, to show the name
	Button->OnHovered.AddDynamic(this, &UBBInventorySlotWidget::OnHover);
	Button->OnUnhovered.AddDynamic(this, &UBBInventorySlotWidget::OnUnhover);
}

void UBBInventorySlotWidget::OnClick()
{
	//Icon->SetVisibility(ESlateVisibility::Visible);
	UBBInventoryComponent* InventoryComponent;
	UBBMouseInventorySlotWidget* MouseSlot;
	if (InventoryWidget)
	{
		InventoryComponent = InventoryWidget->GetOwnerCharacter()->GetInventoryComponent();
		MouseSlot = InventoryWidget->GetMouseSlot()->GetInventorySlot();
	}
	else
	{
		InventoryComponent = Cast<ABBPlayerCharacter>(GetOwningPlayer()->GetPawn())->GetInventoryComponent();
		MouseSlot = CraftingInventoryWidget->GetMouseSlot()->GetInventorySlot();
	}

	if (InventoryComponent != nullptr
		&& MouseSlot != nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(HoverTimer);
		ItemNamePlate->SetVisibility(ESlateVisibility::Hidden);
		//	If the Mouse is Empty & Slot Clicked has something
		if (MouseSlot->GetInventorySlot()->GetItem() == nullptr
			&& InventorySlot->GetItem() != nullptr)
		{
			////UE_LOG(LogTemp, Warning, TEXT("Mouse Empty, Slot Pop"));

			//InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
			InventoryComponent->MoveToSlot(InventorySlot, MouseSlot->GetInventorySlot());
			return;

			//	Move to Mouse
			if (InventoryComponent->MoveToSlot(
				MouseSlot->GetInventorySlot(),
				InventorySlot))
			{
				InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
				return;
			}
		}
		//	If the Mouse has something & Slot Clicked is empty
		if (MouseSlot->GetInventorySlot()->GetItem() != nullptr
			&& InventorySlot->GetItem() == nullptr
			&& !IsOutputSlot)
		{
			////UE_LOG(LogTemp, Warning, TEXT("Mouse Pop, Slot Empty"));

			InventoryComponent->MoveToSlot(MouseSlot->GetInventorySlot(), InventorySlot);
			//InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
			ShowName();
			return;

			//	Move to Inventory Slot
			if (InventoryComponent->MoveToSlot(
				InventorySlot,
				MouseSlot->GetInventorySlot()))
			{
				InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
				return;
			}
		}
		//	If the Mouse has something & Slot Clicked has something
		if (MouseSlot->GetInventorySlot()->GetItem() != nullptr
			&& InventorySlot->GetItem() != nullptr
			&& !IsOutputSlot)
		{
			if (MouseSlot->GetInventorySlot()->GetItem() == InventorySlot->GetItem())
			{
				if (InventoryComponent->CombineStacks(MouseSlot->GetInventorySlot(), InventorySlot))
				{
					ShowName();
					return;
				}
			}
			////UE_LOG(LogTemp, Warning, TEXT("Mouse Pop, Slot Pop"));
			InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
			ShowName();
			return;

			//	Check if they can be combined (into the inventory slot)
			/*if (InventoryComponent->MoveToSlot(
				InventorySlot,
				MouseSlot->GetInventorySlot()))
			{
				return;
			}*/
			//	Swap Stacks
			/*else
			{
				InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
				return;
			}*/
		}
		GetWorld()->GetTimerManager().ClearTimer(HoverTimer);
		ItemNamePlate->SetVisibility(ESlateVisibility::Hidden);
		if (InventorySlot->GetItem() != nullptr)
		{
			//Set the timer
			GetWorld()->GetTimerManager().SetTimer(HoverTimer, this, &UBBInventorySlotWidget::ShowName, 0.5f, false);
		}

	}



	//InventoryComponent->SwapStacks(InventorySlot, MouseSlot->GetInventorySlot());
	//OwningC
}

void UBBInventorySlotWidget::OnHover()
{
	//If the slot has an item, set a timer
	if (InventorySlot->GetItem() != nullptr)
	{
		//Set the timer
		GetWorld()->GetTimerManager().SetTimer(HoverTimer, this, &UBBInventorySlotWidget::ShowName, 0.5f, false);
		/*TArray<UWidget*> widgets;
		widgets = ItemNamePlate->GetAllChildren();
		for (int i = 0; i < widgets.Num(); i++)
		{
			if (widgets[i]->GetName() == "ItemName")
			{
				UTextBlock* text = Cast<UTextBlock>(widgets[i]);
				text->SetText(FText::FromString(InventorySlot->GetItem()->GetItemName()));
			}
		}*/
		//Set the deatils panel item to its item
		if (DetailsPanel != nullptr)
			DetailsPanel->SetItem(InventorySlot->GetItem());
	}
}

void UBBInventorySlotWidget::OnUnhover()
{
	//End the timer if it's started, and if it isn't, hide the nameplate
	if (GetWorld()->GetTimerManager().IsTimerActive(HoverTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(HoverTimer);
	}
	else
	{
		ItemNamePlate->SetVisibility(ESlateVisibility::Hidden);
	}
}
