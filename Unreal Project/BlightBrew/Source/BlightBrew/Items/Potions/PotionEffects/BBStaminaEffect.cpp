// Copyright © Too Many Eyes , 2022


#include "BBStaminaEffect.h"
#include "../../Engine/Public/TimerManager.h"
#include "../../../Characters/CharacterComponents/BBStaminaComponent.h"

bool UBBStaminaEffect::OnUse(TArray<AActor*> actors)
{
    AppliedActors = actors;

    for (int i = 0; i < actors.Num(); i++)
    {
        ABBCharacterBase* gameCharacter = Cast<ABBCharacterBase>(actors[i]);
        if (gameCharacter)
        {
            FTimerHandle timerHandle;
            gameCharacter->GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UBBStaminaEffect::EndEffects, EffectTime);
            timers.Add(timerHandle);
            //Timer isn't working, needs fix

            //Adding stamina to player
            gameCharacter->GetStaminaComponent()->ModifyCurrentStamina(StaminaBonusValue);
                
            //Adding max stamina to player
            gameCharacter->GetStaminaComponent()->ModifyMaxStamina(MaxStaminaBonusValue, EffectTime);
            
            //Adding stamina regen to player
            gameCharacter->GetStaminaComponent()->SetIncrementAmount(gameCharacter->GetStaminaComponent()->GetIncrementAmount() + StaminaRegenBonusValue);


        }
    }

    return true;
}

void UBBStaminaEffect::EndEffects()
{
    //UE_LOG(LogTemp, Warning, TEXT("Timer end"));
    int k = 0;
    for (int i = 0; i < AppliedActors.Num(); i++)
    {
        ABBCharacterBase* gameCharacter = Cast<ABBCharacterBase>(AppliedActors[i]);
        if (gameCharacter)
        {
            //Reset the regen
            gameCharacter->GetStaminaComponent()->SetIncrementAmount(gameCharacter->GetStaminaComponent()->GetIncrementAmount() - StaminaRegenBonusValue);
            k++;
        }
    }
}
