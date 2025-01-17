// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BBPotionComponentBase.h"
#include "BBThrowableComponent.generated.h"


//UCLASS()
UCLASS( classGroup= "Blightbrew|Potion", meta=(BlueprintSpawnableComponent, ShortToolTip="Allows the potion to be used as a throwable. \nThrows in the direction the player is looking, or the direction the nonplayer is facing."))
class BLIGHTBREW_API UBBThrowableComponent : public UBBPotionComponentBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBBThrowableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool OnUse(BBControlType controlType, AActor* instagatingActor) override;
};
