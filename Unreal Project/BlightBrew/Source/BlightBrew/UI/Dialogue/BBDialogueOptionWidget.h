// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "Blueprint/UserWidget.h"
#include "BBDialogueOptionWidget.generated.h"

class UBBDialogueWidget;
class UBBDialogueComponent;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBDialogueOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDialogueWidget(UBBDialogueWidget* widget);
	void SetIndex(int32 index);
	FORCEINLINE int32 GetIndex() { return Index; }

	void SetText(FText text);
	void SetOption(FDialogueOption option);

	FDialogueOption GetOption();

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* Button;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DialogueTextBlock;

	UBBDialogueWidget* DialogueWidget;

	FDialogueOption Option;

	int32 Index;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;


	UFUNCTION()
		void OnClick();
	
};
