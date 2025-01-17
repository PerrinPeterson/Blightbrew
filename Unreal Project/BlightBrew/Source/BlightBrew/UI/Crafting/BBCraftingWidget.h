// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Crafting/BBCraftingStation.h"
#include "BBCraftingWidget.generated.h"

class UBBCraftingInventoryWidget;
class UBBCraftingScreenWidget;
class UBBMouseInventorySlotWidget;
class UBBMouseSlotWidget;
class UTextBlock;
class UBorder;
class ABBPlayerCharacter;
class UBBCraftingBookWidget;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCraftingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	FORCEINLINE ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }
	
	FORCEINLINE bool IsEnabled() { return bIsEnabled; }
	void Toggle(TMap <FBBCraftingRecipe, bool> Recipies, ABBCraftingStation* station);
	UBBMouseInventorySlotWidget* GetMouseSlot();
protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UBBCraftingInventoryWidget* CraftingInventoryWidget;

	UPROPERTY(meta = (BindWidget))
		UBBCraftingScreenWidget* CraftingScreenWidget;

	UBBMouseSlotWidget* MouseSlotWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBBMouseSlotWidget> MouseSlotClass;

	//Crafting Screen Additions
	//The Crafting Book
	UPROPERTY(meta = (BindWidget))
		UBBCraftingBookWidget* CraftingBookWidget;
	
	//The Details Pannel
	UPROPERTY(meta = (BindWidget))
		class UBBDetailsPanel* CraftingDetailsWidget;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;



private:
	ABBPlayerCharacter* OwningCharacter;
	bool bIsEnabled = false;
	
};
