// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBCraftingScreenWidget.generated.h"

class UBBInventorySlotWidget;
class UBBInventorySlotNew;
class UBBCraftingInventoryWidget;
class UBorder;
class UTextBlock;
class ABBPlayerCharacter;
class UButton;
/**
 *
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCraftingScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }
	void SetCraftingInventoryWidget(UBBCraftingInventoryWidget* inWidget) { CraftingInventoryWidget = inWidget; }
	void SetCraftingStation(ABBCraftingStation* station) { craftingStation = station; }
	void SetDetailsPanel(class UBBDetailsPanel* InDetailsPanel) { DetailsPanel = InDetailsPanel; }
protected:
	UBBCraftingInventoryWidget* CraftingInventoryWidget;
	ABBCraftingStation* craftingStation;


	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot1;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot2;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot3;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* OutputSlot;

	UPROPERTY(meta = (BindWidget))
		UButton* Craft;

	UFUNCTION()
		void OnCraft();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;



private:
	ABBPlayerCharacter* OwningCharacter;
	class UBBDetailsPanel* DetailsPanel;
	bool bHasAllocated = false;
	/*UBBInventorySlotNew* slot1;
	UBBInventorySlotNew* slot2;
	UBBInventorySlotNew* slot3;
	UBBInventorySlotNew* slotOut;*/

};
