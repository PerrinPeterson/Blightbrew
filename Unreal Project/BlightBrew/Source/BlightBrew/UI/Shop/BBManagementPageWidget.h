// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBManagementPageWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBManagementPageWidget : public UUserWidget
{
	GENERATED_BODY()

		//Currently, the only use for this page is to open, or close the shop
		
public:
	//Set Owning Player
	void SetOwningPlayer(class ABBPlayerCharacter* owningPlayer) { OwningCharacter = owningPlayer; }

	//Set Owning Book
	void SetOwningBook(class UBBShopBookWidget* owningBook) { OwningBookWidget = owningBook; }
	
protected:
	//Exit Menu Button
	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;
	
	//Open Shop Button
	UPROPERTY(meta = (BindWidget))
		class UButton* OpenShopButton;
	
	//Close Shop Button
	UPROPERTY(meta = (BindWidget))
		class UButton* CloseShopButton;
	
	//Switch pages buttons, need Catalogue, Order, and History
	UPROPERTY(meta = (BindWidget))
		class UButton* CataloguePageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* OrderPageButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* HistoryPageButton;
	
	//Contruct
	virtual void NativeConstruct() override;
	//Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	//Button Functions
	UFUNCTION()
		void ExitButtonClicked();
	UFUNCTION()
		void OpenShopButtonClicked();
	UFUNCTION()
		void CloseShopButtonClicked();
	UFUNCTION()
		void CataloguePageButtonClicked();
	UFUNCTION()
		void OrderPageButtonClicked();
	UFUNCTION()
		void HistoryPageButtonClicked();
	

private:
	//Owning Player
	class ABBPlayerCharacter* OwningCharacter;
	class UBBShopBookWidget* OwningBookWidget;
};
