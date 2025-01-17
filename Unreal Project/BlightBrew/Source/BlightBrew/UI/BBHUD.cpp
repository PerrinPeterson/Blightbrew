// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/BBHUD.h"

//	ENGINE INCLUDES
#include "Engine/Canvas.h"

//	COMPONENT INCLUDES
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ProgressBar.h"
//	Blightbrew Includes
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Crafting/BBCraftingStation.h"
#include "BlightBrew/Inventory/Storage/BBStorageShelf.h"
#include "BlightBrew/UI/Crafting/BBMoneyWidget.h"
#include "BlightBrew/UI/BBBuildStateWidget.h"
#include "BlightBrew/UI/BBFocusTextWidget.h"
#include "BlightBrew/UI/Crafting/BBCraftingWidget.h"
#include "BlightBrew/UI/Inventory/BBStorageWidget.h"
#include "BlightBrew/UI/Journal/BBJournalWidget.h"
#include "BlightBrew/UI/Pause/BBPauseMenuWidget.h"
#include "BlightBrew/UI/Shop/BBShopBookWidget.h"
#include "BlightBrew/UI/Time/BBTimeWidget.h"
#include "Dialogue/BBDialogueScreenWidget.h"
#include "Inventory/BBQuickSlotWidget.h"
#include "Loading/BBLoadingScreenWidget.h"
#include "Loading/BBBlackScreenWidget.h"

ABBHUD::ABBHUD()
{
	//StaminaBar = CreateDefaultSubobject<UProgressBar>(TEXT("StaminaBar"));

	bIsMenuOpen = false;
}

void ABBHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bIsMenuOpen)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Menu Open"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Menu Not Open"));
	}



	if (OwningCharacter)
	{
		// Check if the quickslot character is the same as the owning character
		//if (QuickSlotWidget->GetOwnerCharacter() != OwningCharacter)
		//{
		//	QuickSlotWidget->SetOwnerCharacter(OwningCharacter);
		//}
		//
		//// Check if the journal character is the same as the owning character
		//if (JournalWidget->GetOwnerCharacter() != OwningCharacter)
		//{
		//	JournalWidget->SetOwnerCharacter(OwningCharacter);
		//}
		//
		////Check if the pause menu character is the same as the owning character
		//if (PauseWidget->GetOwnerCharacter() != OwningCharacter)
		//{
		//	PauseWidget->SetOwnerCharacter(OwningCharacter);
		//}
	}
}

void ABBHUD::BeginPlay()
{
	Super::BeginPlay();

	bIsMenuOpen = false;

	OwningCharacter = Cast<ABBPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());



}

void ABBHUD::LateBeginPlay()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());


	BuildStateWidget = CreateWidget<UBBBuildStateWidget>(PC, *BuildStateWidgetClass);

	BuildStateWidget->AddToViewport();

	LoadingScreenWidget = CreateWidget<UBBLoadingScreenWidget>(PC, *LoadingScreenWidgetClass);

	LoadingScreenWidget->AddToViewport();

	GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle,
		this,
		&ABBHUD::LateConstruct, LoadingScreenWidget->GetDelayTime(),
		false);
}

void ABBHUD::LateConstruct()
{
	LoadingScreenWidget->RemoveFromViewport();

	APlayerController* PC = Cast<APlayerController>(GetOwner());

	PauseWidget = CreateWidget<UBBPauseMenuWidget>(PC, *PauseWidgetClass);
	PauseWidget->SetOwnerCharacter(OwningCharacter);
	PauseWidget->AddToViewport();
	//PauseWidget->SetVisibility(ESlateVisibility::Hidden);

	JournalWidget = CreateWidget<UBBJournalWidget>(PC, *JournalWidgetClass);
	JournalWidget->SetOwnerCharacter(OwningCharacter);
	JournalWidget->AddToViewport();
	//JournalWidget->SetVisibility(ESlateVisibility::Hidden);

	QuickSlotWidget = CreateWidget<UBBQuickSlotWidget>(PC, *QuickSlotWidgetClass);
	QuickSlotWidget->SetOwnerCharacter(OwningCharacter);
	QuickSlotWidget->AddToViewport();

	FocusTextWidget = CreateWidget<UBBFocusTextWidget>(PC, *FocusTextWidgetClass);
	FocusTextWidget->SetOwnerCharacter(OwningCharacter);
	FocusTextWidget->AddToViewport();

	TimeWidget = CreateWidget<UBBTimeWidget>(PC, *TimeWidgetClass);
	//TimeWidget->SetOwnerCharacter(OwningCharacter);
	TimeWidget->AddToViewport();

	DialogueScreenWidget = CreateWidget<UBBDialogueScreenWidget>(PC, *DialogueScreenWidgetClass);
	DialogueScreenWidget->AddToViewport();
	DialogueScreenWidget->SetVisibility(ESlateVisibility::Hidden);

	CraftingWidget = CreateWidget<UBBCraftingWidget>(PC, *CraftingWidgetClass);
	CraftingWidget->AddToViewport();
	CraftingWidget->SetVisibility(ESlateVisibility::Hidden);
	
	StorageWidget = CreateWidget<UBBStorageWidget>(PC, *StorageWidgetClass);
	StorageWidget->AddToViewport();
	StorageWidget->SetVisibility(ESlateVisibility::Hidden);

	ShopBookWidget = CreateWidget<UBBShopBookWidget>(PC, *ShopBookWidgetClass);
	ShopBookWidget->AddToViewport();
	ShopBookWidget->SetOwningPlayer(OwningCharacter);
	ShopBookWidget->SetVisibility(ESlateVisibility::Hidden);

	MoneyWidget = CreateWidget<UBBMoneyWidget>(PC, *MoneyWidgetClass);
	MoneyWidget->SetOwningPlayer(OwningCharacter);
	MoneyWidget->AddToViewport();
	MoneyWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	MoneyWidget->SetRenderOpacity(0.0f);

	BlackScreenWidget = CreateWidget<UBBBlackScreenWidget>(PC, *BlackScreenWidgetClass);
	BlackScreenWidget->AddToViewport();
	BlackScreenWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	BlackScreenWidget->SetRenderOpacity(0.0f);

	OwningCharacter->UnPause();
}

void ABBHUD::OpenLevel(FString LevelName)
{
	RemoveWidgetsFromViewport();
}

void ABBHUD::AddWidgetsToViewport()
{
	//QuickSlotWidget->AddToViewport();
	//FocusTextWidget->AddToViewport();
	//TimeWidget->AddToViewport();

	QuickSlotWidget->SetVisibility(ESlateVisibility::Visible);
	FocusTextWidget->SetVisibility(ESlateVisibility::Visible);
	TimeWidget->SetVisibility(ESlateVisibility::Visible);
	MoneyWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void ABBHUD::RemoveWidgetsFromViewport()
{
	//QuickSlotWidget->RemoveFromViewport();
	//FocusTextWidget->RemoveFromViewport();
	//TimeWidget->RemoveFromViewport();

	QuickSlotWidget->SetVisibility(ESlateVisibility::Hidden);
	FocusTextWidget->SetVisibility(ESlateVisibility::Hidden);
	TimeWidget->SetVisibility(ESlateVisibility::Hidden);
	MoneyWidget->SetVisibility(ESlateVisibility::Hidden);

	PauseWidget->RemoveFromViewport();
}

void ABBHUD::ToggleQuickSlotWidget()
{
	CheckQuickSlotWidget();
}

void ABBHUD::CheckQuickSlotWidget()
{
	if (QuickSlotWidget == nullptr)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		QuickSlotWidget = CreateWidget<UBBQuickSlotWidget>(PC, *QuickSlotWidgetClass);
		QuickSlotWidget->SetOwnerCharacter(OwningCharacter);
		QuickSlotWidget->AddToViewport();
	}
}

void ABBHUD::ToggleJournalWidget()
{

	CheckJournalWidget();

	if (bIsMenuOpen)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Menu Opening."));

		RemoveWidgetsFromViewport();

		if (!JournalWidget->IsInViewport())
		{
			JournalWidget->AddToViewport();
		}
		JournalWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Menu Closing."));
		JournalWidget->SetVisibility(ESlateVisibility::Hidden);
		//JournalWidget->RemoveFromViewport();
		AddWidgetsToViewport();
	}
}

void ABBHUD::CheckJournalWidget()
{
	if (JournalWidget == nullptr)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		JournalWidget = CreateWidget<UBBJournalWidget>(PC, *JournalWidgetClass);
		JournalWidget->SetOwnerCharacter(OwningCharacter);
	}
}

void ABBHUD::ToggleInventory()
{
	if (CraftingWidget->IsEnabled() || StorageWidget->IsEnabled() || ShopBookWidget->IsEnabled())
		return;
	bIsMenuOpen = JournalWidget->SwitchActiveWidget(EJournalWidgetType::Inventory);

	ToggleJournalWidget();
}

void ABBHUD::ToggleCrafting(TMap <FBBCraftingRecipe, bool> Recipies, ABBCraftingStation* station)
{
	//Opens the crafting menu, this is a standalone, and isnt a part of the journal widget
	if (CraftingWidget)
	{
		//For testing, very basic. Prob won't be ale to interact with it. Will change to an internal toggle, which will handle the visibility and interaction
		CraftingWidget->Toggle(Recipies, station);
		bIsMenuOpen = CraftingWidget->IsEnabled();
		if (bIsMenuOpen)
			RemoveWidgetsFromViewport();
		else
			AddWidgetsToViewport();
	}
}

void ABBHUD::ToggleStorage(ABBStorageShelf* shelf)
{
	if (StorageWidget)
	{
		if(shelf)
			shelf->SetNeedsUpdate(true);
		//For testing, very basic. Prob won't be ale to interact with it. Will change to an internal toggle, which will handle the visibility and interaction
		StorageWidget->Toggle(shelf);
		bIsMenuOpen = StorageWidget->IsEnabled();
		if (bIsMenuOpen)
			RemoveWidgetsFromViewport();
		else
			AddWidgetsToViewport();
	}
}

void ABBHUD::ToggleJournal()
{
	if (CraftingWidget->IsEnabled() || StorageWidget->IsEnabled() || ShopBookWidget->IsEnabled())
		return;
	CheckJournalWidget();
	bIsMenuOpen = JournalWidget->SwitchActiveWidget(EJournalWidgetType::Journal);

	ToggleJournalWidget();
}

void ABBHUD::SwitchJournalPage(EJournalWidgetType Page)
{
	CheckJournalWidget();
	bIsMenuOpen = JournalWidget->SwitchActiveWidget(Page);

	ToggleJournalWidget();
}

void ABBHUD::ToggleMap()
{
	if (CraftingWidget->IsEnabled() || StorageWidget->IsEnabled() || ShopBookWidget->IsEnabled())
		return;
	CheckJournalWidget();
	bIsMenuOpen = JournalWidget->SwitchActiveWidget(EJournalWidgetType::Map);

	ToggleJournalWidget();
}



void ABBHUD::TogglePause(bool toggle)
{
	if (PauseWidget)
	{
		/*if (bIsMenuOpen)
			return;*/
		if (toggle)
		{
			PauseWidget->AddToViewport();
			PauseWidget->Pause();
		}
		else
		{
			PauseWidget->RemoveFromViewport();
		}
	}

}

void ABBHUD::StartDialogue(UBBDialogueComponent* instigator)
{

	if (DialogueScreenWidget != nullptr
		&& instigator != nullptr)
	{
		if (instigator->GetDialogues().Num() > 0)
		{
			OwningCharacter->StartDialogue();
			DialogueScreenWidget->SetVisibility(ESlateVisibility::Visible);
			DialogueScreenWidget->StartDialogue(instigator);
		}


	}

}

void ABBHUD::EndDialogue()
{
	if (DialogueScreenWidget != nullptr)
	{
		OwningCharacter->EndDialogue();
		DialogueScreenWidget->SetVisibility(ESlateVisibility::Hidden);

	}
}

void ABBHUD::DialogueInput()
{
	DialogueScreenWidget->DialogueInput();
}

void ABBHUD::CloseOpenMenu()
{
	//Should close all Journal Widgets
	CheckJournalWidget();
	if (JournalWidget->IsEnabled())
	{
		bIsMenuOpen = JournalWidget->SwitchActiveWidget(JournalWidget->GetActiveWidget());
		ToggleJournalWidget();
	}
	else if (CraftingWidget->IsEnabled())
	{
		TMap<FBBCraftingRecipe, bool> Recipies;
		ToggleCrafting(Recipies, nullptr);
		OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
	}
	else if (StorageWidget->IsEnabled())
	{
		ToggleStorage(nullptr);
		OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
	}
	else if (ShopBookWidget->IsEnabled())
	{
		ShopBookWidget->Toggle();
		OwningCharacter->ToggleInputMode(EInputMode::GameOnly);
	}
	//Close the Pause Menu
	/*if (PauseWidget)
		if (PauseWidget->IsInViewport())
		{
			TogglePause(false);
		}*/
}
