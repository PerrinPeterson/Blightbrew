// Copyright © Too Many Eyes , 2022 - 2023


#include "BBManagementPageWidget.h"
//Unreal Includes
#include "Components/Button.h"
//BlightBrew Includes
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/UI/Shop/BBShopBookWidget.h"
#include "BlightBrew/Shop/BBShopBook.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"

void UBBManagementPageWidget::NativeConstruct()
{
	//Bind the buttons
	ExitButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::ExitButtonClicked);
	OpenShopButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::OpenShopButtonClicked);
	CloseShopButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::CloseShopButtonClicked);
	CataloguePageButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::CataloguePageButtonClicked);
	OrderPageButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::OrderPageButtonClicked);
	HistoryPageButton->OnClicked.AddDynamic(this, &UBBManagementPageWidget::HistoryPageButtonClicked);
}

void UBBManagementPageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Grey out the buttons if the shop is already open or closed
	if (OwningBookWidget)
	{
		if (OwningBookWidget->GetOwningBook()->Shop->GetShopOpenStatus())
		{
			OpenShopButton->SetIsEnabled(false);
			CloseShopButton->SetIsEnabled(true);
		}
		else
		{
			OpenShopButton->SetIsEnabled(true);
			CloseShopButton->SetIsEnabled(false);
		}
	}
}

void UBBManagementPageWidget::ExitButtonClicked()
{
	if (OwningBookWidget)
	{
		if(OwningCharacter)
			OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
		OwningBookWidget->Toggle();
	}
}

void UBBManagementPageWidget::OpenShopButtonClicked()
{
	if (OwningBookWidget)
	{
		if (OwningBookWidget->GetOwningBook()->Shop->GetShopOpenStatus())
		{
			//Shop is already open, so do nothing
			return;
		}
		else
		{
			//Shop is closed, so open it
			OwningBookWidget->GetOwningBook()->Shop->SetShopOpenStatus(true);
		}
		
	}
}

void UBBManagementPageWidget::CloseShopButtonClicked()
{
	if (OwningBookWidget)
	{
		if (OwningBookWidget->GetOwningBook()->Shop->GetShopOpenStatus())
		{
			//Shop is open, so close it
			OwningBookWidget->GetOwningBook()->Shop->SetShopOpenStatus(false);
		}
		else
		{
			//Shop is already closed, so do nothing
			return;
		}
	}
}

void UBBManagementPageWidget::CataloguePageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_CATALOGUE);
	}
}

void UBBManagementPageWidget::OrderPageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_ORDER);
	}
}

void UBBManagementPageWidget::HistoryPageButtonClicked()
{
	if (OwningBookWidget)
	{
		OwningBookWidget->SetPage(PAGE::PAGE_HISTORY);
	}
}
