// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../BBPotionBase.h"
#include "BBPotionComponentBase.generated.h"


UCLASS(classGroup = "Blightbrew|Potion")
class BLIGHTBREW_API UBBPotionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBBPotionComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//TODO: Implement this function for Inherted classes
	virtual bool OnUse(BBControlType controlType, AActor* instagatingActor) {
		return false;
	};



};

