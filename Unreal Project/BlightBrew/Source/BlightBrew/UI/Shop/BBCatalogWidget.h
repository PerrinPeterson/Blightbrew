// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blightbrew/Items/BBBaseItem.h"
#include "BBCatalogWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBCatalogWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	//Scroll Box
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* CatalogScrollBox;
	
	//Catalog Entries Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catalog")
		TArray<class UBBCatalogEntryWidget*> CatalogEntries;
	
	//Catlog Entry Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catalog")
		TSubclassOf<class UBBCatalogEntryWidget> CatalogEntryClass;
	
	//Currently Selected Item
	TSubclassOf<class ABBBaseItem> SelectedItem;
	
public:
	//Refresh Catalog
	UFUNCTION(BlueprintCallable)
		void RefreshCatalog(TMap<TSubclassOf<ABBBaseItem>, int64> itemCatalog);
	//Sort the Catalog
	UFUNCTION(BlueprintCallable)
		void SortCatalog();
	//Get the currently selected item
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class ABBBaseItem> GetSelectedItem() { return SelectedItem; }
	//Refresh the selected items Entry Widget
	UFUNCTION(BlueprintCallable)
		void RefreshSelectedItemEntry();
	//Set the currently selected item
	UFUNCTION(BlueprintCallable)
		void SetSelectedItem(TSubclassOf<class ABBBaseItem> InItem) { SelectedItem = InItem; }
	

	bool AlphebeticalSort(const TSubclassOf<class ABBBaseItem>& A, const TSubclassOf<class ABBBaseItem>& B);
};
