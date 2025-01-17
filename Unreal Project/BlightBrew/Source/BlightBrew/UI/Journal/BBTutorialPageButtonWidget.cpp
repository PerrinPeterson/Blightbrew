// Copyright © Too Many Eyes , 2022 - 2023


#include "BBTutorialPageButtonWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Blightbrew/UI/Journal/BBTutorialPageWidget.h"


void UBBTutorialPageButtonWidget::SetTitle(FString NewTitle)
{
	Title = NewTitle;
	TitleText->SetText(FText::FromString(Title));
}

void UBBTutorialPageButtonWidget::SetPageSwitcher(UWidgetSwitcher* NewPageSwitcher)
{
	PageSwitcher = NewPageSwitcher;
}

void UBBTutorialPageButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TitleText->SetText(FText::FromString(Title));
	Button->OnClicked.AddDynamic(this, &UBBTutorialPageButtonWidget::OnButtonClicked);
	
}

void UBBTutorialPageButtonWidget::OnButtonClicked()
{
	TArray<UWidget*> pages = PageSwitcher->GetAllChildren();
	for (int i = 0; i < pages.Num(); i++)
	{
		UBBTutorialPageWidget* page = Cast<UBBTutorialPageWidget>(pages[i]);
		if (page->Title == Title)
		{
			PageSwitcher->SetActiveWidget(page);
			break;
		}	
	}
}
