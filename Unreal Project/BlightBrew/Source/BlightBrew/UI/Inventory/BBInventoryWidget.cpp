// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Inventory/BBInventoryWidget.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/UI/BBMouseSlotWidget.h"
#include "BlightBrew/UI/Crafting/BBCraftingInventoryWidget.h"
#include "BlightBrew/UI/Inventory/BBDetailsPanel.h"

void UBBInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	OwningCharacter = Cast<ABBPlayerCharacter>(GetOwningPlayerPawn());

	if (MouseSlot == nullptr)
	{
		MouseSlot = CreateWidget<UBBMouseSlotWidget>(GetWorld(), MouseSlotClass);
		MouseSlot->AddToViewport();
		MouseSlot->SetOwnerCharacter(OwningCharacter);
	}

	if (OwningCharacter
		&& !bHasAllocated)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character Valid"));
		int counter = 0;

		TArray<UBBInventorySlotNew*> InventorySlots = OwningCharacter->GetInventoryComponent()->GetInventorySlots();
		if(InventoryWidget->InventorySlot1->SetInventorySlot(InventorySlots[0]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot2->SetInventorySlot(InventorySlots[1]))
		{
			counter++;
		}
		if (InventoryWidget->InventorySlot3->SetInventorySlot(InventorySlots[2]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot4->SetInventorySlot(InventorySlots[3]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot5->SetInventorySlot(InventorySlots[4]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot6->SetInventorySlot(InventorySlots[5]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot7->SetInventorySlot(InventorySlots[6]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot8->SetInventorySlot(InventorySlots[7]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot9->SetInventorySlot(InventorySlots[8]))
		{
			counter++;
		}
		if(InventoryWidget->InventorySlot10->SetInventorySlot(InventorySlots[9]))
		{
			counter++;
		}
		//UE_LOG(LogTemp, Warning, TEXT("%i"), counter);
		if(counter == 10)
		{
			bHasAllocated = true;
		}

		TArray<UBBInventorySlotNew*> QuickSlots = OwningCharacter->GetInventoryComponent()->GetQuickSlots();

		QuickSlotWidget1->SetInventorySlot(QuickSlots[0]);
		QuickSlotWidget2->SetInventorySlot(QuickSlots[1]);
		QuickSlotWidget3->SetInventorySlot(QuickSlots[2]);

		if (InventoryWidget->InventorySlot1->IsVisible())
		{
			//UE_LOG(LogTemp, Warning, TEXT("InvSlot is visible"));
		}

		MouseSlot->SetInventorySlot(OwningCharacter->GetInventoryComponent()->GetMouseSlot());
		
	}
}

void UBBInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwningCharacter = Cast<ABBPlayerCharacter>(GetOwningPlayerPawn());

	if (OwningCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character Valid"));

		TArray<UBBInventorySlotNew*> InventorySlots = OwningCharacter->GetInventoryComponent()->GetInventorySlots();
		InventoryWidget->InventorySlot1->SetInventorySlot(InventorySlots[0]);
		InventoryWidget->InventorySlot2->SetInventorySlot(InventorySlots[1]);
		InventoryWidget->InventorySlot3->SetInventorySlot(InventorySlots[2]);
		InventoryWidget->InventorySlot4->SetInventorySlot(InventorySlots[3]);
		InventoryWidget->InventorySlot5->SetInventorySlot(InventorySlots[4]);
		InventoryWidget->InventorySlot6->SetInventorySlot(InventorySlots[5]);
		InventoryWidget->InventorySlot7->SetInventorySlot(InventorySlots[6]);
		InventoryWidget->InventorySlot8->SetInventorySlot(InventorySlots[7]);
		InventoryWidget->InventorySlot9->SetInventorySlot(InventorySlots[8]);
		InventoryWidget->InventorySlot10->SetInventorySlot(InventorySlots[9]);


		TArray<UBBInventorySlotNew*> QuickSlots = OwningCharacter->GetInventoryComponent()->GetQuickSlots();

		QuickSlotWidget1->SetInventorySlot(QuickSlots[0]);
		QuickSlotWidget2->SetInventorySlot(QuickSlots[1]);
		QuickSlotWidget3->SetInventorySlot(QuickSlots[2]);


	}

	InventoryWidget->InventorySlot1->SetInventoryWidget(this);
	InventoryWidget->InventorySlot2->SetInventoryWidget(this);
	InventoryWidget->InventorySlot3->SetInventoryWidget(this);
	InventoryWidget->InventorySlot4->SetInventoryWidget(this);
	InventoryWidget->InventorySlot5->SetInventoryWidget(this);
	InventoryWidget->InventorySlot6->SetInventoryWidget(this);
	InventoryWidget->InventorySlot7->SetInventoryWidget(this);
	InventoryWidget->InventorySlot8->SetInventoryWidget(this);
	InventoryWidget->InventorySlot9->SetInventoryWidget(this);
	InventoryWidget->InventorySlot10->SetInventoryWidget(this);

	QuickSlotWidget1->SetInventoryWidget(this);
	QuickSlotWidget2->SetInventoryWidget(this);
	QuickSlotWidget3->SetInventoryWidget(this);

	//MouseSlot->SetInventoryWidget(this);

	InventoryWidget->SetDetailsPanel(DetailsPanel);
	DetailsPanel->ClearItem();

	QuickSlotWidget1->DetailsPanel = DetailsPanel;
	QuickSlotWidget2->DetailsPanel = DetailsPanel;
	QuickSlotWidget3->DetailsPanel = DetailsPanel;
}

void UBBInventoryWidget::Hide()
{
	//Hides all the widgets from the viewport
	InventoryWidget->InventorySlot1->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot2->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot3->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot4->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot5->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot6->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot7->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot8->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot9->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidget->InventorySlot10->SetVisibility(ESlateVisibility::Hidden);
	
	QuickSlotWidget1->SetVisibility(ESlateVisibility::Hidden);
	QuickSlotWidget2->SetVisibility(ESlateVisibility::Hidden);
	QuickSlotWidget3->SetVisibility(ESlateVisibility::Hidden);
	
	MouseSlot->SetVisibility(ESlateVisibility::Hidden);
}

void UBBInventoryWidget::Show()
{
	//Shows all the widgets from the viewport
	InventoryWidget->InventorySlot1->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot2->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot3->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot4->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot5->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot6->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot7->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot8->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot9->SetVisibility(ESlateVisibility::Visible);
	InventoryWidget->InventorySlot10->SetVisibility(ESlateVisibility::Visible);

	QuickSlotWidget1->SetVisibility(ESlateVisibility::Visible);
	QuickSlotWidget2->SetVisibility(ESlateVisibility::Visible);
	QuickSlotWidget3->SetVisibility(ESlateVisibility::Visible);

	MouseSlot->SetVisibility(ESlateVisibility::Visible);
}
