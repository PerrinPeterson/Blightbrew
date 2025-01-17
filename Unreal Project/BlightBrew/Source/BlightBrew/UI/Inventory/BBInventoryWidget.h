// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBInventorySlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "BBInventoryWidget.generated.h"

class UBBMouseSlotWidget;
class ABBPlayerCharacter;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	UBBMouseSlotWidget* GetMouseSlot() { return MouseSlot; }
protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	/*UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;*/

	/*UPROPERTY(meta = (BindWidget))
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

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot7;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot8;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot9;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot10;*/

	UPROPERTY(meta = (BindWidget))
		class UBBCraftingInventoryWidget* InventoryWidget;

	ABBPlayerCharacter* OwningCharacter;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget1;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget2;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget3;

	UPROPERTY(meta = (BindWidget))
		class UBBDetailsPanel* DetailsPanel;

	//MOVE TO ITS OWN WIDGET THAT RENDERS ON TOP OF INVENTORY
	//UPROPERTY(meta = (BindWidget))
		UBBMouseSlotWidget* MouseSlot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBBMouseSlotWidget> MouseSlotClass;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	void Hide();
	void Show();
private:
	bool bHasAllocated = false;
	
};
