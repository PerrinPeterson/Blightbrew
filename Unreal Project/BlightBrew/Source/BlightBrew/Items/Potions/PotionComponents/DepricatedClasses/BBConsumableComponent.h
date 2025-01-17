// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBPotionComponentBase.h"
#include "BBConsumableComponent.generated.h"

/**
 * 
 */
UCLASS(classGroup = "Blightbrew|Potion", meta = (BlueprintSpawnableComponent, ShortToolTip = "Allows the potion to be Consumed. \nUsed to apply effects to the consumer"))
class BLIGHTBREW_API UBBConsumableComponent : public UBBPotionComponentBase
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UBBConsumableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool OnUse(BBControlType controlType, AActor* instagatingActor) override;
	
};
