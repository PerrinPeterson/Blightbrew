// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBMainMenuWidget.generated.h"

class UButton;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* LoadGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
		void OnNew();

	UFUNCTION()
		void OnLoad();

	UFUNCTION()
		void OnSettings();

	UFUNCTION()
		void OnCredits();

	UFUNCTION()
		void OnQuit();
	
};
