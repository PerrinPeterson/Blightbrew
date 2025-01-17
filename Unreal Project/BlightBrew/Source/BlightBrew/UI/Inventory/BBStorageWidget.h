// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBStorageWidget.generated.h"

/**
 * 
 */
class UBBStorageInventoryWidget;
class UBBCraftingInventoryWidget;
class UBBMouseInventorySlotWidget;
class UBBMouseSlotWidget;
class ABBPlayerCharacter;
UCLASS(Abstract)
class BLIGHTBREW_API UBBStorageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	FORCEINLINE ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }
	
	void Toggle(class ABBStorageShelf* Shelf);
	FORCEINLINE bool IsEnabled() { return bIsEnabled; }
	UBBMouseInventorySlotWidget* GetMouseSlot();
	
protected:
	
	UPROPERTY(meta = (BindWidget))
		UBBCraftingInventoryWidget* CraftingInventoryWidget;
	
	UPROPERTY(meta = (BindWidget))
		UBBStorageInventoryWidget* StorageInventoryWidget;

	UPROPERTY(meta = (BindWidget))
		class UBBDetailsPanel* CraftingDetailsWidget;

	UBBMouseSlotWidget* MouseSlotWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBBMouseSlotWidget> MouseSlotClass;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;
	

private:
	ABBPlayerCharacter* OwningCharacter;
	bool bIsEnabled = false;
};
