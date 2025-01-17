// Copyright © Too Many Eyes , 2022
/*The Etherial Vision Effect, Designed by Perrin Peterson, 02/07/2023
* This effect is to be used to grant the player the ability to see RevealableActors in the world for a set amount of time.
* This effect needs to;
*	- Grant the player the ability to see RevealableActors in the world for a set amount of time.
*	- Remove the ability to see RevealableActors in the world after the set amount of time.
*/

#pragma once

#include "CoreMinimal.h"
#include "BBEffect.h"
#include "BBEtherialVisionEffect.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBEtherialVisionEffect : public UBBEffect
{
	GENERATED_BODY()
	
public:
	
	bool OnUse(TArray<AActor*> actors) override;
	void EndEffects();

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew | Potion | Effects")
		int64 EffectTime;
};
