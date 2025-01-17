// Copyright © Too Many Eyes , 2022 - 2023


#include "BBTutorialJournalWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Blueprint/WidgetTree.h"
#include "BlightBrew/UI/Journal/BBTutorialPageButtonWidget.h"

void UBBTutorialJournalWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//We're going to create a button for each page title, and add it to the scroll box.
	for (FString Title : PageTitles)
	{
		//Create the button
		UBBTutorialPageButtonWidget* Button = CreateWidget<UBBTutorialPageButtonWidget>(GetWorld(), ButtonClass);
		Button->SetTitle(Title);
		Button->SetPageSwitcher(PageSwitcher);
		
		//Add the button to the scroll box
		PageExplorerScrollBox->AddChild(Button);
	}
}
