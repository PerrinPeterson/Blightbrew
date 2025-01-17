 // Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBStaminaBar.generated.h"

class ABBCharacterBase;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBStaminaBar : public UUserWidget
{
	GENERATED_BODY()

public:
		void SetOwnerCharacter(ABBCharacterBase* InCharacter) { OwningCharacter = InCharacter; }

protected:
	ABBCharacterBase* OwningCharacter;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentStaminaLabel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MaxStaminaLabel;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
