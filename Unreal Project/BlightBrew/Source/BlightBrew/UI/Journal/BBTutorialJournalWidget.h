// Copyright © Too Many Eyes , 2022 - 2023
/* A simple widget that will display the tutorial journal. All it needs is two bound variables, a scroll box on the left, and a widget swicher on the right.
*  The left will be an array of strings, the right will switch between the tutorial pages. The left will be a bunch of buttons that will call the switcher to switch to the correct page.
* 
*  What I'll need;
*	- A scroll box that will hold the buttons
*	- An array of strings that will be the names of the buttons, an will reprisent the titles.
*	- A widget Switcher that will switch to a widget that has the same Title as the button that was pressed.
*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBTutorialJournalWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBTutorialJournalWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* PageExplorerScrollBox;
	
	//Only will hold tutorial pages. These will be little more than a scroll box, with various widgets in it, but importantly they will have a title.
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* PageSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew")
		TArray<FString> PageTitles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew")
		TSubclassOf<class UBBTutorialPageButtonWidget> ButtonClass;

protected:
	virtual void NativeConstruct() override;
	

	
	
};
