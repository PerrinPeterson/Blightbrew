// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBDialogueScreenWidget.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "Blueprint/UserWidget.h"
#include "BBDialogueWidget.generated.h"

class UBBDialogueOptionWidget;
class UBorder;
class UTextBlock;
class UScrollBox;
class UBBDialogueComponent;

/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetDialogueComponent(UBBDialogueComponent* dialogue);
	void SetTargetDialogue(FString dialogue);

	void OnOptionClicked(UBBDialogueOptionWidget* widget);

	void DialogueInput();

protected:
	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UBBDialogueComponent* DialogueComponent;

	UPROPERTY(meta = (BindWidget))
		UScrollBox* DialogueOptions;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SpeakerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DialogueTextBlock;

	UPROPERTY(BlueprintReadOnly)
		FString CurrentDialogue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString TargetDialogue;

	UPROPERTY(BlueprintReadOnly)
		FDialogue ActiveDialogue;

	UPROPERTY(BlueprintReadOnly)
		int32 ActiveDialogueIndex;

	UPROPERTY(BlueprintReadOnly)
		int32 DialogueIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DialogueBufferTime;

	FTimerHandle DialogueTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UBBDialogueOptionWidget> OptionClass;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void SkipCurrentDialogue();

	void NextDialogueCharacter();

	void StartDialogue();

	void NextDialogue();

	void EndDialogue();

	

	UFUNCTION()
		void OnTimerFinished();

	void ShowDialogueOptions();
	void HideDialogueOptions();

	bool bIsTimerFinished = true;
	bool bIsCurrentDialogueFinished = false;
	bool bIsChoosingOption = false;

	
};
