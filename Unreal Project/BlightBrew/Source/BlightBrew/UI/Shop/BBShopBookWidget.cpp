// Copyright © Too Many Eyes , 2022 - 2023


#include "BBShopBookWidget.h"
//Unreal Includes
#include "Components/WidgetSwitcher.h"

//BlightsBrew Includes
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BBManagementPageWidget.h"
#include "BBCatalogPageWidget.h"
#include "BBShopOrderPageWidget.h"
// #include "BBShopHistoryWidget.h"


void UBBShopBookWidget::Toggle()
{
	bIsEnabled = !bIsEnabled;
	SetVisibility(bIsEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	//Need to put the player in a state where they are considered to be in a menu
	OwningCharacter->SetIsInMenu(bIsEnabled);
	if (bIsEnabled)
		OwningCharacter->GetHUD()->RemoveWidgetsFromViewport();
	else
		OwningCharacter->GetHUD()->AddWidgetsToViewport();
	if (bIsEnabled)
	{
		OwningCharacter->ToggleInputMode(EInputMode::GameAndUI);
		//Maybe need some logic here, we'll see
		ManagementPage->SetOwningBook(this);
		ManagementPage->SetOwningPlayer(OwningCharacter);
		CataloguePage->SetOwningBook(this);
		CataloguePage->SetOwningPlayer(OwningCharacter);
		CataloguePage->RefreshCatalogue();
		CataloguePage->OnToggle();
		OrderPage->SetOwningBook(this);
		OrderPage->SetOwningPlayer(OwningCharacter);
		OrderPage->OnToggle();
	}
}

void UBBShopBookWidget::SetPage(PAGE page)
{
	CurrentPage = page;
	PageSwitcher->SetActiveWidgetIndex((int)page);
}

void UBBShopBookWidget::NativeConstruct()	
{
	Super::NativeConstruct();
	ManagementPage->SetOwningBook(this);
	ManagementPage->SetOwningPlayer(OwningCharacter);
	CataloguePage->SetOwningBook(this);
	CataloguePage->SetOwningPlayer(OwningCharacter);
	//Set the default page to the management page
	SetPage(PAGE::PAGE_MANAGEMENT);
}
