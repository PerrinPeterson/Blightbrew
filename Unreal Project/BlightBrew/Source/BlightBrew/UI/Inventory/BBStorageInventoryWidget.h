// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBStorageInventoryWidget.generated.h"

class UBBInventorySlotWidget;
class ABBPlayerCharacter;
class ABBStorageShelf;
class UBBCraftingInventoryWidget;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBStorageInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	void SetShelf(class ABBStorageShelf* InShelf);
	void SetCraftingInventoryWidget(UBBCraftingInventoryWidget* inWidget);

	void SetDetailsPanel(class UBBDetailsPanel* InDetailsPanel) { DetailsPanel = InDetailsPanel; }
protected:
	UBBCraftingInventoryWidget* CraftingInventoryWidget;
	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot1;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot2;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot3;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot4;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot5;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot6;

	ABBPlayerCharacter* OwningCharacter;
	ABBStorageShelf* Shelf;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

private:
	class UBBDetailsPanel* DetailsPanel;
	
};
