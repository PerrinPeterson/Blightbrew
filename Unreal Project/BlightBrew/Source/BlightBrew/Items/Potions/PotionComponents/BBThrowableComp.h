// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBPotionComponent.h"
#include "BBThrowableComp.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBThrowableComp : public UBBPotionComponent
{
	GENERATED_BODY()

public:

	virtual bool OnUse(AActor* instagatingItem, BBControlType controlType, AActor* instagatingActor) override;
	
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:
	bool bThrown = false;
};
