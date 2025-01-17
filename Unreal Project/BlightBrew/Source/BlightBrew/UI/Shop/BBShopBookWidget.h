// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBShopBookWidget.generated.h"

UENUM(BlueprintType)
enum PAGE
{
	PAGE_MANAGEMENT		UMETA(DisplayName = "Management"),
	PAGE_CATALOGUE		UMETA(DisplayName = "Catalogue"),
	PAGE_ORDER			UMETA(DisplayName = "Order"),
	PAGE_HISTORY		UMETA(DisplayName = "History")
};

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBShopBookWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void Toggle();
	void SetPage(PAGE page);
	PAGE GetPage() { return CurrentPage; }
	bool IsEnabled() { return bIsEnabled; }
	void SetOwningPlayer(class ABBPlayerCharacter* owningPlayer) { OwningCharacter = owningPlayer; }
	void SetOwningBook(class ABBShopBook* owningBook) { OwningBook = owningBook; }
	class ABBShopBook* GetOwningBook() { return OwningBook; }
	
protected:
	virtual void NativeConstruct() override;
	
	// Management Page
	UPROPERTY(meta = (BindWidget))
		class UBBManagementPageWidget* ManagementPage;
	
	// Catalogue Page
	UPROPERTY(meta = (BindWidget))
		class UBBCatalogPageWidget* CataloguePage;
	
	// Order Page
	UPROPERTY(meta = (BindWidget))
		class UBBShopOrderPageWidget* OrderPage;
	
	// History Page
	/*UPROPERTY(meta = (BindWidget))
		class UBBShopHistoryWidget* HistoryPage;*/
	
	// Page Switcher
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* PageSwitcher;
	
	//Current Page
	class ABBPlayerCharacter* OwningCharacter;
	class ABBShopBook* OwningBook;
	PAGE CurrentPage;
	bool bIsEnabled = false;
	
};
