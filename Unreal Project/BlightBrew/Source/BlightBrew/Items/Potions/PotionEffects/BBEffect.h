// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBEffect.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT, EditInlineNew, BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBEffect : public UObject
{
	GENERATED_BODY()

public:

	virtual bool OnUse(TArray<AActor*> actors) { return true; };
	
protected:
	TArray<AActor*> AppliedActors;
};
