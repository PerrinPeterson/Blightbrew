// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Stamina/BBStaminaBar.h"

#include "BlightBrew/Characters/BBCharacterBase.h"
#include "BlightBrew/Characters/CharacterComponents/BBStaminaComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBBStaminaBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(OwningCharacter == nullptr)
	{
		return;
	}

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	CurrentStaminaLabel->SetText(FText::AsNumber(OwningCharacter->GetStaminaComponent()->GetStamina(), &Opts));
	MaxStaminaLabel->SetText(FText::AsNumber(OwningCharacter->GetStaminaComponent()->GetMaxStamina(), &Opts));

	float perc = OwningCharacter->GetStaminaComponent()->GetStamina() / OwningCharacter->GetStaminaComponent()->GetMaxStamina();
	StaminaBar->SetPercent(perc);

	if(OwningCharacter->GetStaminaComponent()->IsModified())
	{
		StaminaBar->SetFillColorAndOpacity(FLinearColor::Yellow);
	}
	else
	{
		StaminaBar->SetFillColorAndOpacity(FLinearColor::Green);
	}
}
