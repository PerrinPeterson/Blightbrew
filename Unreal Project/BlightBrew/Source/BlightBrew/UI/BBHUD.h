// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Crafting/BBCraftingWidget.h"
#include "BBHUD.generated.h"

class UBBDialogueComponent;
enum class EJournalWidgetType;
class ABBPlayerCharacter;
class UBBJournalWidget;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABBHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }

	void LateBeginPlay();

	void LateConstruct();

	void OpenLevel(FString LevelName);

public:
	// Add all widgets to the viewport
	void AddWidgetsToViewport();

	// Remove all widgets from the viewport
	void RemoveWidgetsFromViewport();

protected:
	// Toggle the QuickSlotWidget
	void ToggleQuickSlotWidget();

	// check if the QuickSlotWidget is valid
	void CheckQuickSlotWidget();

	// Toggle the journal widget
	void ToggleJournalWidget();

	// Check if the journal widget is valid
	void CheckJournalWidget();


public:
	// Getter for if the Menu is Open
	UFUNCTION(BlueprintCallable)
		bool GetIsMenuOpen() { return bIsMenuOpen; }

	// Toggle Inventory Widget
	UFUNCTION(BlueprintCallable)
		void ToggleInventory();

	// Toggle Crafting Widget
	UFUNCTION(BlueprintCallable)
		void ToggleCrafting(TMap <FBBCraftingRecipe, bool> Recipies, ABBCraftingStation* station);
	
	// Toggle Storage Widget
	UFUNCTION(BlueprintCallable)
		void ToggleStorage(class ABBStorageShelf* shelf);

	// Toggle Journal Widget
	UFUNCTION(BlueprintCallable)
		void ToggleJournal();

	// Switch Journal Page
	UFUNCTION(BlueprintCallable)
		void SwitchJournalPage(EJournalWidgetType Page);

	// Toggle Map Widget
	UFUNCTION(BlueprintCallable)
		void ToggleMap();

	// Toggle Pause Widget
	UFUNCTION(BlueprintCallable)
		void TogglePause(bool toggle);

	void StartDialogue(UBBDialogueComponent* instigator);
	void EndDialogue();
	void DialogueInput();

	void CloseOpenMenu();
	void SetIsMenuOpen(bool b) { bIsMenuOpen = b; }
	class UBBShopBookWidget* GetShopBookWidget() { return ShopBookWidget; }
	class UBBBlackScreenWidget* GetBlackScreenWidget() { return BlackScreenWidget; }

private:

	bool bIsMenuOpen;

	ABBPlayerCharacter* OwningCharacter;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBBQuickSlotWidget* QuickSlotWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UBBQuickSlotWidget> QuickSlotWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBJournalWidget* JournalWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBJournalWidget> JournalWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBPauseMenuWidget* PauseWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBPauseMenuWidget> PauseWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBFocusTextWidget* FocusTextWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBFocusTextWidget> FocusTextWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBTimeWidget* TimeWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBTimeWidget> TimeWidgetClass;

	//Money Widget
	UPROPERTY(VisibleAnywhere)
		class UBBMoneyWidget* MoneyWidget;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UBBMoneyWidget> MoneyWidgetClass;
	

	UPROPERTY(VisibleAnywhere)
		class UBBBuildStateWidget* BuildStateWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBBuildStateWidget> BuildStateWidgetClass;


	UPROPERTY(VisibleAnywhere)
		class UBBDialogueScreenWidget* DialogueScreenWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBDialogueScreenWidget> DialogueScreenWidgetClass;


	//


	UPROPERTY(VisibleAnywhere)
		class UBBLoadingScreenWidget* LoadingScreenWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class TSubclassOf<UBBLoadingScreenWidget> LoadingScreenWidgetClass;

	UPROPERTY(VisibleAnywhere)
		UBBCraftingWidget* CraftingWidget;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UBBCraftingWidget> CraftingWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBStorageWidget* StorageWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UBBStorageWidget> StorageWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBShopBookWidget* ShopBookWidget;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UBBShopBookWidget> ShopBookWidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UBBBlackScreenWidget* BlackScreenWidget;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UBBBlackScreenWidget> BlackScreenWidgetClass;

	FTimerHandle LoadingTimerHandle;

};
