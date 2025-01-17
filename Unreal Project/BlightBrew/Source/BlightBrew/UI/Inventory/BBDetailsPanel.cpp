// Copyright © Too Many Eyes , 2022 - 2023


#include "BBDetailsPanel.h"
//Unreal Includes
#include "Components/Image.h"
#include "Components/TextBlock.h"

//BlightBrew Includes
#include "../../Items/BBBaseItem.h"

//*Sets the item to display, and updates the UI
void UBBDetailsPanel::SetItem(ABBBaseItem* Item)
{
	//Set the widgets
	if (Item == nullptr)
		return;
		
	ItemIcon->SetBrushFromTexture(Item->GetIcon());
	ItemIcon->SetOpacity(1.0f);
	ItemName->SetText(FText::FromString(Item->GetItemName()));
	ItemDescription->SetText(FText::FromString(Item->GetItemDescription()));
}

void UBBDetailsPanel::ClearItem()
{
	//Set the widgets
	ItemIcon->SetBrushFromTexture(nullptr);
	ItemIcon->SetOpacity(0.0f);
	ItemName->SetText(FText::FromString(""));
	ItemDescription->SetText(FText::FromString(""));
}

FString UBBDetailsPanel::GetItemName()
{
	return ItemName->Text.ToString();
}
