// Copyright © Too Many Eyes , 2022 - 2023
/*A custom widget, Designed by Perrin Peterson, 03/16/2023
* This widget is suppoed to be the players window into the crafting system.
* It needs to;
*  - Dynamically create a list of all the recipes the player can craft, and display them in a list.
*  - Be hoverable, and display a tooltip when hovered over.
*  - Hide certain recipes if the player doesn't have the required knowledge.
*  - Have the list be scrollable, and dynamically resize itself to fit the number of recipes, so we don't have to manually add recipes to the list.
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Crafting/BBCraftingStation.h"
#include "BBCraftingBookWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBCraftingBookWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Called on startup
	virtual void NativeConstruct() override;
	
	//Called every frame
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Called when the widget is shown, for refreshing the recipe list.
	void OnShown(TMap <FBBCraftingRecipe, bool> InRecipeList);

	//The Plus image, this goes between the first and second item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTexture2D*> PlusImages;

	//The Equals image, this goes between the second and third item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* EqualsImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Line;
	
protected:
	
	//The Scroll Box that contains the list of recipes.
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* RecipeList;
	
	//The Array of Horizontal Boxes that contain the recipe images, these will be populated in code.
	UPROPERTY(BlueprintReadOnly)
		TArray<class UHorizontalBox*> RecipeBoxes;

	//The Array of Images, these will be populated in code. We need these to clean up the widget when it's hidden.
	UPROPERTY(BlueprintReadOnly)
		TArray<class UImage*> RecipeImages;
		
	
	
	
};
