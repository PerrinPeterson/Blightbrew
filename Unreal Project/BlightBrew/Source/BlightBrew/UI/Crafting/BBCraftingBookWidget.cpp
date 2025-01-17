// Copyright © Too Many Eyes , 2022 - 2023


#include "BBCraftingBookWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "Math/UnrealMathUtility.h"

void UBBCraftingBookWidget::NativeConstruct()
{
	
}

void UBBCraftingBookWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UBBCraftingBookWidget::OnShown(TMap <FBBCraftingRecipe, bool> Recipies)
{
	//Clear the Recipe List
	RecipeList->ClearChildren();
	
	
	//Loop through, and create 3 things:
	//1. Item 1, this needs an image that can be hovered over, and a tooltip that displays the item name.
	//2. Item 2, this needs an image that can be hovered over, and a tooltip that displays the item name.
	//3. An output Item, this needs an image that can be hovered over, and a tooltip that displays the item name.
	//If the player doesn't have the required knowledge, the items should be greyed out, and the tooltip should display "Unknown Item".
	for (auto& Recipe : Recipies)
	{
		if (Recipe.Key.isRepeat)
			continue;
		//For each, create 3 image widgets, and add them to the list.
		//If the player doesn't have the required knowledge, grey out the images.

		//Create the Horizontal Box
		UHorizontalBox* NewHorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
		
		

		//Add the Horizontal Box to the Scroll Box
		RecipeList->AddChild(NewHorizontalBox);
		//Add the Horizontal Box to the Array
		RecipeBoxes.Add(NewHorizontalBox);
		


		//Create the Item Image
		UImage* NewImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		//Add the Image to the Horizontal Box
		NewHorizontalBox->AddChild(NewImage);
		//Add the Image to the Array
		RecipeImages.Add(NewImage);

		//If the player doesn't have the required knowledge, grey out the image.
		if (Recipe.Value == false)
		{
			NewImage->SetColorAndOpacity(FLinearColor(0.5, 0.5, 0.5, 1));
		}
		else
		{
			//Stupid me, we now need to do this three times.
			NewImage->SetBrushFromTexture(Recipe.Key.ItemOne.GetDefaultObject()->GetIcon());
		}
		NewImage->SetBrushSize(FVector2D(64, 64));
		
		//Create an Image for the + sign
		UImage* NewImagePlus = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		//Add the Image to the Horizontal Box
		NewHorizontalBox->AddChild(NewImagePlus);
		//Set the brush to our '+' Texture
		int32 num = FMath::RandRange(0, PlusImages.Num() - 1);
		NewImagePlus->SetBrushFromTexture(PlusImages[num]);
		//Add the Image to the Array
		RecipeImages.Add(NewImagePlus);
		NewImagePlus->SetBrushSize(FVector2D(64, 64));

		
		//Create the Item Image
		UImage* NewImageTwo = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		//Add the Image to the Horizontal Box
		NewHorizontalBox->AddChild(NewImageTwo);
		//Add the Image to the Array
		RecipeImages.Add(NewImageTwo);
		

		//If the player doesn't have the required knowledge, grey out the image.
		if (Recipe.Value == false)
		{
			NewImageTwo->SetColorAndOpacity(FLinearColor(0.5, 0.5, 0.5, 1));
		}
		else
		{
			//Stupid me, we now need to do this three times.
			NewImageTwo->SetBrushFromTexture(Recipe.Key.ItemTwo.GetDefaultObject()->GetIcon());
		}
		NewImageTwo->SetBrushSize(FVector2D(64, 64));
		
		//Create an Image for the = sign
		UImage* NewImageEquals = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		//Add the Image to the Horizontal Box
		NewHorizontalBox->AddChild(NewImageEquals);
		//Add the Image to the Array
		RecipeImages.Add(NewImageEquals);
		NewImageEquals->SetBrushSize(FVector2D(64, 64));
		

		//Create the Item Image
		UImage* NewImageOutput = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		//Add the Image to the Horizontal Box
		NewHorizontalBox->AddChild(NewImageOutput);
		//Add the Image to the Array
		RecipeImages.Add(NewImageOutput);

		//If the player doesn't have the required knowledge, grey out the image.
		if (Recipe.Value == false)
		{
			NewImageOutput->SetColorAndOpacity(FLinearColor(0.5, 0.5, 0.5, 1));
		}
		else
		{
			//Stupid me, we now need to do this three times.
			NewImageOutput->SetBrushFromTexture(Recipe.Key.OutputItem.GetDefaultObject()->GetIcon());
		}
		NewImageOutput->SetBrushSize(FVector2D(64, 64));

		UHorizontalBox* LineGap = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
		//Add the Horizontal Box to the Scroll Box
		RecipeList->AddChild(LineGap);
		//Add the Horizontal Box to the Array
		RecipeBoxes.Add(LineGap);
		UImage* LineImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		LineImage->SetBrushFromTexture(Line, true);
		//Add the Image to the Horizontal Box
		LineGap->AddChild(LineImage);
		LineImage->SetBrushSize(FVector2D(384, 16));
		//Add the Image to the Array
		RecipeImages.Add(LineImage);
	}

	//for (int i = 0; i < RecipeImages.Num(); i++)
	//{
	//	//Need to do some actual math here.
	//	RecipeImages[i]->SetBrushSize(FVector2D(64, 64));
	//	
	//}
}

