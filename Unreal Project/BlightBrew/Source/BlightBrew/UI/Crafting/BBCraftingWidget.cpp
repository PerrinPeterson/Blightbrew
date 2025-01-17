// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Crafting/BBCraftingWidget.h"
//Unreal Includes
//BlightBrew Includes
#include "BBCraftingScreenWidget.h"
#include "BlightBrew/UI/Crafting/BBCraftingBookWidget.h"
#include "BlightBrew/UI/Crafting/BBCraftingInventoryWidget.h"
#include "../BBMouseSlotWidget.h"
#include "../Inventory/BBDetailsPanel.h"
#include "../Inventory/BBMouseInventorySlotWidget.h"
#include "../../Characters/Player/BBPlayerCharacter.h"
#include "../../Inventory/BBInventoryComponent.h"

void UBBCraftingWidget::Toggle(TMap <FBBCraftingRecipe, bool> Recipies, ABBCraftingStation* station)
{
	bIsEnabled = !bIsEnabled;
	SetVisibility(bIsEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	//Need to put the player in a state where they are considered to be in a menu
	OwningCharacter->SetIsInMenu(bIsEnabled);
	if (bIsEnabled)
	{ 
		CraftingBookWidget->OnShown(Recipies);
		CraftingScreenWidget->SetCraftingStation(station);
		CraftingInventoryWidget->SetDetailsPanel(CraftingDetailsWidget);
		CraftingDetailsWidget->ClearItem();
		CraftingScreenWidget->SetDetailsPanel(CraftingDetailsWidget);
	}
}

UBBMouseInventorySlotWidget* UBBCraftingWidget::GetMouseSlot()
{
	return CraftingInventoryWidget->GetMouseSlot()->GetInventorySlot();
}

void UBBCraftingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CraftingInventoryWidget->GetOwnerCharacter() == nullptr)
	{
		CraftingInventoryWidget->SetOwnerCharacter(OwningCharacter);
		CraftingScreenWidget->SetCraftingInventoryWidget(CraftingInventoryWidget);
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

void UBBCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwningCharacter = Cast<ABBPlayerCharacter>(GetOwningPlayerPawn());
	
	CraftingInventoryWidget->SetOwnerCharacter(OwningCharacter);
	CraftingScreenWidget->SetCraftingInventoryWidget(CraftingInventoryWidget);
}
