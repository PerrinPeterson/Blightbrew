// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBDialogueScreenWidget.generated.h"

class UBBDialogueComponent;
class UBBDialogueWidget;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBDialogueScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		void StartDialogue(UBBDialogueComponent* Instigator);
		void EndDialogue();
		void DialogueInput();

protected:
	UPROPERTY(meta = (BindWidget))
		UBBDialogueWidget* Dialogue;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UBBDialogueComponent* CurrentDialogueComponent;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;
	
};
