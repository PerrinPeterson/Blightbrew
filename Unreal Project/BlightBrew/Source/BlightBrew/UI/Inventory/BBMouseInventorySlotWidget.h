// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBMouseInventorySlotWidget.generated.h"

class ABBPlayerCharacter;
class UBBInventorySlotNew;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBMouseInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool SetInventorySlot(UBBInventorySlotNew* InInventorySlot);
	UBBInventorySlotNew* GetInventorySlot() { return InventorySlot; }

	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

protected:

	UBBInventorySlotNew* InventorySlot;

	UPROPERTY(meta = (BindWidget))
		UImage* Icon;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Quantity;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	ABBPlayerCharacter* OwningCharacter;
	bool bIsHidden;
	
};
