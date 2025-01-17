// Copyright © Too Many Eyes , 2022 - 2023
/*A Details Panel, Designed by Perrin Peterson, 03/26/2023
* This panel is designed to display the details of an item, like the name, description, and Icon.
* The panel will be used anywhere that you can click on an item slot.
* The panel needs to;
*  - Display the name of the item
*  - Display the description of the item
*  - Display the icon of the item
*  - Accept 'Events' from other UI elements, accepting the item to display
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBDetailsPanel.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBDetailsPanel : public UUserWidget
{
	GENERATED_BODY()
		
//Children Widgets		
protected: 
	//Item Icon
	UPROPERTY(meta = (BindWidget))
		class UImage* ItemIcon;
	
	//Item Name
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemName;

	//Item Description
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemDescription;

//Functions
public:
	//Set the item to display
	void SetItem(class ABBBaseItem* Item);
	
	//Clear the item to display
	void ClearItem();

	class FString GetItemName();
	

	
};
