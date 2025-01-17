// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/BBMouseInventorySlotWidget.h"
#include "BBMouseSlotWidget.generated.h"

class UBBMouseInventorySlotWidget;
class UBBInventorySlotNew;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBMouseSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInventorySlot(UBBInventorySlotNew* InInventorySlot) { InventorySlot->SetInventorySlot(InInventorySlot); }
	UBBMouseInventorySlotWidget* GetInventorySlot() { return InventorySlot; }

	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { InventorySlot->SetOwnerCharacter(InCharacter); }


protected:
		UPROPERTY(meta = (BindWidget))
			UBBMouseInventorySlotWidget* InventorySlot;

		void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

		void NativeConstruct() override;
	
};
