// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBEffect.h"
#include "../../../Characters/BBCharacterBase.h"
#include "BBStaminaEffect.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBStaminaEffect : public UBBEffect
{
	GENERATED_BODY()

public:
	bool OnUse(TArray<AActor*> actors) override;

	void EndEffects();

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew | Potion | Effects")
		int64 StaminaBonusValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew | Potion | Effects")
		int64 MaxStaminaBonusValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew | Potion | Effects")
		int64 StaminaRegenBonusValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew | Potion | Effects")
		int64 EffectTime;

	TArray<FTimerHandle> timers;
};
