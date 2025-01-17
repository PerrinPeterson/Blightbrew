// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBPotionComponent.h"
#include "BBConsumableComp.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBConsumableComp : public UBBPotionComponent
{
	GENERATED_BODY()
	
public:
	virtual bool OnUse(AActor* instagatingItem, BBControlType controlType, AActor* instagatingActor) override;

};
