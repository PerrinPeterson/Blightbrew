// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseEffect.generated.h"


UCLASS( ClassGroup=(Custom))
class BLIGHTBREW_API UBBBaseEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBBBaseEffect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool OnUse(TArray<AActor*> actors);

protected:
	TArray<AActor*> AppliedActors;
		
};
