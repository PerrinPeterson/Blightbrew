// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBJournalWidget.generated.h"

class UBBInventoryWidget;
class UBorder;
class UUserWidget;
class UWidgetSwitcher;
class UTextBlock;
class ABBPlayerCharacter;

UENUM()
enum class EJournalWidgetType
{
	Map,
	Inventory,
	Journal,
};

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBJournalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter);

	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	bool SwitchActiveWidget(EJournalWidgetType widgetType);

	bool ToggleEnabled();

	bool IsEnabled();

	void Hide();
	void Show();

	EJournalWidgetType GetActiveWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* MapImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* MapImageFaded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* InventoryImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* InventoryImageFaded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* JournalImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew")
		class UTexture2D* JournalImageFaded;

protected:
	ABBPlayerCharacter* OwningCharacter;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
		UUserWidget* MapWidgetComp;

	UPROPERTY(meta = (BindWidget))
		UBBInventoryWidget* InventoryWidgetComp;

	UPROPERTY(meta = (BindWidget))
		class UBBTutorialJournalWidget* TutorialWidgetComp;

	/*UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;*/

	UPROPERTY(meta = (BindWidget))
		class UButton* MapButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* InventoryButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JournalButton;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnMapButtonClicked();
	UFUNCTION()
		void OnInventoryButtonClicked();
	UFUNCTION()
		void OnJournalButtonClicked();

private:
	bool ToggleEnableAndVisibility(bool isEnabled);
};
