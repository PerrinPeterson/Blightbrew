// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBCraftingInventoryWidget.generated.h"

class UBBInventorySlotWidget;
class UTextBlock;
class UBorder;
class UBBMouseSlotWidget;
class ABBPlayerCharacter;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCraftingInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	UBBMouseSlotWidget* GetMouseSlot() { return MouseSlot; }
	void SetDetailsPanel(class UBBDetailsPanel* InDetailsPanel) { DetailsPanel = InDetailsPanel; }
protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Money;

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

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot7;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot8;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot9;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* InventorySlot10;

protected:
	ABBPlayerCharacter* OwningCharacter;

	UBBMouseSlotWidget* MouseSlot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBBMouseSlotWidget> MouseSlotClass;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

private:
	class UBBDetailsPanel* DetailsPanel;

	
};
