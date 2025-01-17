// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Journal/BBJournalWidget.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/UI/Inventory/BBInventoryWidget.h"
#include "BlightBrew/UI/Journal/BBTutorialJournalWidget.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UBBJournalWidget::SetOwnerCharacter(ABBPlayerCharacter* InCharacter)
{
	OwningCharacter = InCharacter;
	InventoryWidgetComp->SetOwnerCharacter(InCharacter);
}

bool UBBJournalWidget::SwitchActiveWidget(EJournalWidgetType widgetType)
{
	switch(widgetType)
	{
		case EJournalWidgetType::Map:
		{
			//WidgetSwitcher->SetActiveWidget(MapWidgetComp);

			if (WidgetSwitcher->GetActiveWidget() == MapWidgetComp
				&& Border->GetIsEnabled())
			{
				//UE_LOG(LogTemp, Warning, TEXT("Map Already Open"));
				return ToggleEnableAndVisibility(false);
			}
			if(WidgetSwitcher->GetActiveWidget() == MapWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(MapWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Map"));
				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != MapWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(MapWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Map"));
				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != MapWidgetComp
				&& Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(MapWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Switching to Map"));
				//return ToggleEnableAndVisibility(true);
			}
			UImage* buttonImage = static_cast<UImage*>(MapButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(MapImageFaded);
			
			buttonImage = static_cast<UImage*>(InventoryButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(InventoryImage);

			buttonImage = static_cast<UImage*>(JournalButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(JournalImage);
			return ToggleEnableAndVisibility(true);
			
		}
		case EJournalWidgetType::Inventory:
		{
			if (WidgetSwitcher->GetActiveWidget() == InventoryWidgetComp
				&& Border->GetIsEnabled())
			{
				//UE_LOG(LogTemp, Warning, TEXT("Inventory Already Open"));

				return ToggleEnableAndVisibility(false);
			}
			if (WidgetSwitcher->GetActiveWidget() == InventoryWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(InventoryWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Inventory"));

				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != InventoryWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(InventoryWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Inventory"));
				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != InventoryWidgetComp
				&& Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(InventoryWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Switching to Inventory"));
				//return ToggleEnableAndVisibility(true);
			}
			UImage* buttonImage = static_cast<UImage*>(MapButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(MapImage);

			buttonImage = static_cast<UImage*>(InventoryButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(InventoryImageFaded);

			buttonImage = static_cast<UImage*>(JournalButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(JournalImage);
			return ToggleEnableAndVisibility(true);
		}
		case EJournalWidgetType::Journal:
		{
			if (WidgetSwitcher->GetActiveWidget() == TutorialWidgetComp
				&& Border->GetIsEnabled())
			{
				//UE_LOG(LogTemp, Warning, TEXT("Tutorial Already Open"));

				return ToggleEnableAndVisibility(false);
			}
			if (WidgetSwitcher->GetActiveWidget() == TutorialWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(TutorialWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Tutorial"));

				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != TutorialWidgetComp
				&& !Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(TutorialWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Opening Tutorial"));
				//return ToggleEnableAndVisibility(true);
			}
			if (WidgetSwitcher->GetActiveWidget() != TutorialWidgetComp
				&& Border->GetIsEnabled())
			{
				WidgetSwitcher->SetActiveWidget(TutorialWidgetComp);
				//UE_LOG(LogTemp, Warning, TEXT("Switching to Tutorial"));
				//return ToggleEnableAndVisibility(true);
			}
			UImage* buttonImage = static_cast<UImage*>(MapButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(MapImage);

			buttonImage = static_cast<UImage*>(InventoryButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(InventoryImage);

			buttonImage = static_cast<UImage*>(JournalButton->GetChildAt(0));
			if (buttonImage)
				buttonImage->SetBrushFromTexture(JournalImageFaded);
			return ToggleEnableAndVisibility(true);
		}
		default:
		{
			WidgetSwitcher->SetActiveWidget(nullptr);
			if (Border->GetIsEnabled())
			{
				//UE_LOG(LogTemp, Warning, TEXT("Closing Journal"));

				return ToggleEnableAndVisibility(false);
			}
		}
		
	}

	WidgetSwitcher->SetActiveWidget(nullptr);
	if (Border->GetIsEnabled())
	{
		//UE_LOG(LogTemp, Warning, TEXT("[INVALID] Closing Journal"));

		return ToggleEnableAndVisibility(false);
	}

	return false;
}

bool UBBJournalWidget::ToggleEnabled()
{
	return ToggleEnableAndVisibility(!Border->GetIsEnabled());
}

bool UBBJournalWidget::IsEnabled()
{
	return Border->GetIsEnabled();
}

void UBBJournalWidget::Hide()
{
	//Hides all the widgets from the viewport
	Border->SetVisibility(ESlateVisibility::Hidden);
	WidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	MapWidgetComp->SetVisibility(ESlateVisibility::Hidden);
	InventoryWidgetComp->SetVisibility(ESlateVisibility::Hidden);
	//TitleTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UBBJournalWidget::Show()
{
	Border->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
	MapWidgetComp->SetVisibility(ESlateVisibility::Visible);
	InventoryWidgetComp->SetVisibility(ESlateVisibility::Visible);
	//TitleTextBlock->SetVisibility(ESlateVisibility::Visible);
}

EJournalWidgetType UBBJournalWidget::GetActiveWidget()
{
	if (WidgetSwitcher->GetActiveWidget() == InventoryWidgetComp)
	{
		return EJournalWidgetType::Inventory;
	}
	else if (WidgetSwitcher->GetActiveWidget() == TutorialWidgetComp)
	{
		return EJournalWidgetType::Journal;
	}
	else
	{
		return EJournalWidgetType::Map;
	}
}

void UBBJournalWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	//if (OwningCharacter == nullptr)
	{
		return;
	}

}

void UBBJournalWidget::NativeConstruct()
{
	Border->SetIsEnabled(false);
	Border->SetVisibility(ESlateVisibility::Hidden);

	WidgetSwitcher->SetActiveWidget(MapWidgetComp);
	
	MapButton->OnClicked.AddDynamic(this, &UBBJournalWidget::OnMapButtonClicked);
	InventoryButton->OnClicked.AddDynamic(this, &UBBJournalWidget::OnInventoryButtonClicked);
	JournalButton->OnClicked.AddDynamic(this, &UBBJournalWidget::OnJournalButtonClicked);
}

void UBBJournalWidget::OnMapButtonClicked()
{
	if (WidgetSwitcher->GetActiveWidget() == MapWidgetComp)
		return;
	SwitchActiveWidget(EJournalWidgetType::Map);
}

void UBBJournalWidget::OnInventoryButtonClicked()
{
	if (WidgetSwitcher->GetActiveWidget() == InventoryWidgetComp)
		return;
	SwitchActiveWidget(EJournalWidgetType::Inventory);
}

void UBBJournalWidget::OnJournalButtonClicked()
{
	if (WidgetSwitcher->GetActiveWidget() == TutorialWidgetComp)
		return;
	SwitchActiveWidget(EJournalWidgetType::Journal);
}

bool UBBJournalWidget::ToggleEnableAndVisibility(bool isEnabled)
{
	Border->SetIsEnabled(isEnabled);

	if(isEnabled)
	{
		Border->SetVisibility(ESlateVisibility::Visible);
		OwningCharacter->ToggleInputMode(EInputMode::GameAndUI);
		return true;
	}
	else
	{
		Border->SetVisibility(ESlateVisibility::Hidden);
		OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
		return false;
	}
}
