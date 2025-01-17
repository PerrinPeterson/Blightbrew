// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBPauseScreenWidget.generated.h"

class UBBSettingsWidget;
class ABBPlayerCharacter;
class UBorder;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBPauseScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }

	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	void ToggleEnabled(bool enabled);

	void Pause();

protected:
	ABBPlayerCharacter* OwningCharacter;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBlock;

	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	UFUNCTION()
	void OnResume();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnQuit();

private:
	void ToggleEnableAndVisibility(bool isEnabled);
};
