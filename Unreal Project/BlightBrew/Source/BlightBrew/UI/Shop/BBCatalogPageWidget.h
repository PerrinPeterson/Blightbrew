// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBCatalogPageWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCatalogPageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Set Owning Player
	void SetOwningPlayer(class ABBPlayerCharacter* owningPlayer) { OwningCharacter = owningPlayer; }

	//Set Owning Book
	void SetOwningBook(class UBBShopBookWidget* owningBook) { OwningBookWidget = owningBook; }

	void RefreshCatalogue();
	void SortCatalogue();
	void OnToggle();

protected:
	//A Catalogue Widget, which replaces our scroll box, and is used to display the items
	UPROPERTY(meta = (BindWidget))
		class UBBCatalogWidget* CatalogueWidget;
	
	//Details Half
	//Details Panel
	UPROPERTY(meta = (BindWidget))
		class UBBDetailsPanel* DetailsPanel;
	//Quick adjust buttons, +1, +5, -1, -5
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustPlusOneButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustPlusFiveButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustMinusOneButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* QuickAdjustMinusFiveButton;

	//An editable text box, to set a custom price
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* CustomPriceTextBox;
	
	
	//Exit Menu Button
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;
	
	//Switch pages buttons, need Catalogue, Order, and History
	UPROPERTY(meta = (BindWidget))
		class UButton* ManagementPageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* OrderPageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* HistoryPageButton;
	
	//Contruct
	virtual void NativeConstruct() override;
	//Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetCurrentlySelectedItem(TSubclassOf<class ABBBaseItem> itemClass);

	//Button Functions
	UFUNCTION()
		void ExitButtonClicked();
	UFUNCTION()
		void ManagementPageButtonClicked();
	UFUNCTION()
		void OrderPageButtonClicked();
	UFUNCTION()
		void HistoryPageButtonClicked();
	UFUNCTION()
		void QuickAdjustPlusOneButtonClicked();
	UFUNCTION()
		void QuickAdjustPlusFiveButtonClicked();
	UFUNCTION()
		void QuickAdjustMinusOneButtonClicked();
	UFUNCTION()
		void QuickAdjustMinusFiveButtonClicked();
	UFUNCTION()
		void CustomPriceTextBoxChanged(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
		void OnTextChanged(const FText& Text);
	
private:

	//Owning Player
	class ABBPlayerCharacter* OwningCharacter;
	class UBBShopBookWidget* OwningBookWidget;
	int32 CurrentSelectedIndex = -1;
	TSubclassOf<class ABBBaseItem> CurrentSelectedItem = nullptr;
	int64 LastEnteredNumber;
};
