// Copyright © Too Many Eyes , 2022


#include "BBConsumableComp.h"


bool UBBConsumableComp::OnUse(AActor* instagatingItem, BBControlType controlType, AActor* instagatingActor)
{
    bool bSuccess = false;
    if (controlType == BBControlType::CONSUME)
    {
        if (instagatingActor == nullptr)
            return false;

        //TODO: use an internal array of effects

        if (Effects.IsEmpty())
        {
            //UE_LOG(LogTemp, Warning, TEXT("ConsumableComponent - No Effects found."));
            return false;
        }

        for (int i = 0; i < Effects.Num(); i++)
        {
            TArray<AActor*> actors;
            actors.Add(instagatingActor);
            if (Effects[i]->OnUse(actors))
                bSuccess = true;
        }

    }
    return bSuccess;
}
