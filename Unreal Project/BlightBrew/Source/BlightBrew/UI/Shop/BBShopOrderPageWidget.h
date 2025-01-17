// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBShopOrderPageWidget.generated.h"

/**
 *
 */
UCLASS()
class BLIGHTBREW_API UBBShopOrderPageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//Set Owning Player
	void SetOwningPlayer(class ABBPlayerCharacter* owningPlayer) { OwningCharacter = owningPlayer; }

	//Set Owning Book
	void SetOwningBook(class UBBShopBookWidget* owningBook) { OwningBookWidget = owningBook; }

	void OnToggle();

protected:

	//Catalog Widget
	UPROPERTY(meta = (BindWidget))
		class UBBCatalogWidget* CatalogWidget;

	//Details Widget
	UPROPERTY(meta = (BindWidget))
		class UBBDetailsPanel* DetailsWidget;

	//Buy Button
	UPROPERTY(meta = (BindWidget))
		class UButton* BuyButton;

	//Buy Number Widgets
	//Quick adjust buttons, +1, +5, -1, -5
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustPlusOneButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustPlusFiveButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustMinusOneButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustMinusFiveButton;

	//An editable text box, to set a buy amount
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* BuyAmountTextBox;

	//Exit Menu Button
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;

	//Switch pages buttons, need Catalogue, Order, and History
	UPROPERTY(meta = (BindWidget))
		class UButton* ManagementPageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* CatalogPageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* HistoryPageButton;

	//Money Icon
	UPROPERTY(meta = (BindWidget))
		class UImage* MoneyIcon;
	//Money Amount
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MoneyAmountText;

	//Native Construct
	virtual void NativeConstruct() override;

	//Native Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Button Functions
	UFUNCTION()
		void OnBuyButtonPressed();
	UFUNCTION()
		void OnQuickAdjustPlusOneButtonPressed();
	UFUNCTION()
		void OnQuickAdjustPlusFiveButtonPressed();
	UFUNCTION()
		void OnQuickAdjustMinusOneButtonPressed();
	UFUNCTION()
		void OnQuickAdjustMinusFiveButtonPressed();
	UFUNCTION()
		void OnExitButtonPressed();
	UFUNCTION()
		void OnManagementPageButtonPressed();
	UFUNCTION()
		void OnCatalogPageButtonPressed();
	UFUNCTION()
		void OnHistoryPageButtonPressed();
	UFUNCTION()
		void OnTextChanged(const FText& Text);

	//TMap of items that can be bought, and their prices
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
		TMap<TSubclassOf<class ABBBaseItem>, int64> ItemsForSale;

private:
	//Owning Player
	class ABBPlayerCharacter* OwningCharacter;
	//Owning Book
	class UBBShopBookWidget* OwningBookWidget;
	//Selected Item
	TSubclassOf<class ABBBaseItem> SelectedItem;
	int64 LastEnteredNumber = 0;

	int64 BuyAmount = 0;

};
