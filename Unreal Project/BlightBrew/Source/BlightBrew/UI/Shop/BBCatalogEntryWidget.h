// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBCatalogEntryWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCatalogEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Pointer to the item that this widget represents
	UPROPERTY(BlueprintReadOnly, Category = "Catalog Entry")
		TSubclassOf<class ABBBaseItem> Item;

	//The Button That surrounds this widget
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button;
	
	// The image of the item
	UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;
	
	// The price of the item
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* PriceText;
	
	// A image for the currency
	UPROPERTY(Meta = (BindWidget))
		class UImage* CurrencyImage;
	
	// The name of the item
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemNameText;

	//Pointer to the parent Catalog Widget
	UPROPERTY(BlueprintReadOnly, Category = "Catalog Entry")
		class UBBCatalogWidget* CatalogWidget;

	//Native Construct
	virtual void NativeConstruct() override;
	
	//Native Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Button functions
	UFUNCTION()
		void OnButtonClicked();

public:
	void SetItem(TSubclassOf <class ABBBaseItem > InItem);
	void SetPrice(int32 InPrice);
	void SetCatalogWidget(class UBBCatalogWidget* InCatalogWidget);
	FString GetItemName() { return Item.GetDefaultObject()->GetName(); }
};
