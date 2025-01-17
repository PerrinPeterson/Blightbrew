// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Inventory/BBInventorySlotDep.h"
#include "Blueprint/UserWidget.h"
#include "BBInventorySlotWidget.generated.h"


class UBBInventoryWidget;
class UBBCraftingInventoryWidget;
class UBBInventorySlotNew;
class UButton;
class UTextBlock;
class UImage;
class UBorder;
class UCanvasPanel;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool SetInventorySlot(UBBInventorySlotNew* InInventorySlot);
	const UBBInventorySlotNew* GetInventorySlot() { return InventorySlot; }

	void SetInventoryWidget(UBBInventoryWidget* InWidget) { InventoryWidget = InWidget; }
	void SetCraftingInventoryWidget(UBBCraftingInventoryWidget* InWidget) { CraftingInventoryWidget = InWidget; }
	UBBCraftingInventoryWidget* GetCraftingInventoryWidget() { return CraftingInventoryWidget; }
	bool IsWidgetSet() { return InventoryWidget != nullptr || CraftingInventoryWidget != nullptr; }
	void ShowName();
	
	//If the slot can't be pushed to.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		bool IsOutputSlot;

	//A pointer to a details panel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UBBDetailsPanel* DetailsPanel;

	void DisableButton();
	void EnableButton();
protected:
	UBBInventorySlotNew* InventorySlot;
	UBBInventoryWidget* InventoryWidget;
	UBBCraftingInventoryWidget* CraftingInventoryWidget;
	FTimerHandle HoverTimer;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UImage* Icon;

	UPROPERTY(meta = (BindWidget))
		UImage* Outline;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Quantity;

	UPROPERTY(meta = (BindWidget))
		UButton* Button;

	UPROPERTY(meta = (BindWidget))
		UImage* ItemQuantityAmount;

	UPROPERTY(meta = (BindWidget))
		UImage* SlotBackground;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* ItemNamePlate;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnClick();

	UFUNCTION()
		void OnHover();
	UFUNCTION()
		void OnUnhover();
};
