// Copyright © Too Many Eyes , 2022


#include "BBConsumableComponent.h"
//#include "../PotionEffects/BaseEffect.h"

UBBConsumableComponent::UBBConsumableComponent()
{
}

void UBBConsumableComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBBConsumableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBBConsumableComponent::OnUse(BBControlType controlType, AActor* instagatingActor)
{
    /*bool bSuccess = false;
    if (controlType == BBControlType::CONSUME)
    {
        if (instagatingActor == nullptr)
            return false;

        TArray<UBBBaseEffect*> ComponentArray;
        GetOwner()->GetComponents<UBBBaseEffect>(ComponentArray);

        if (ComponentArray.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("ConsumableComponent - No Effects found."));
            return false;
        }

        for (int i = 0; i < ComponentArray.Num(); i++)
        {
            TArray<AActor*> actors;
            actors.Add(instagatingActor);
            if (ComponentArray[i]->OnUse(actors))
                bSuccess = true;
        }

    }
    return bSuccess;*/
    return false;
}
