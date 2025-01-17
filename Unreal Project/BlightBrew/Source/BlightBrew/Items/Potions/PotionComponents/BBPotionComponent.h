// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../BBBaseItem.h"
#include "../PotionEffects/BBEffect.h"
#include "BBPotionComponent.generated.h"


/**
 *
 */
UCLASS(ABSTRACT, EditInlineNew, BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBPotionComponent : public UObject
{
    GENERATED_BODY()
public:

    virtual bool OnUse(AActor* instagatingItem, BBControlType controlType, AActor* instagatingActor) { return false; }

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
        TArray<UBBEffect*> Effects;
};
