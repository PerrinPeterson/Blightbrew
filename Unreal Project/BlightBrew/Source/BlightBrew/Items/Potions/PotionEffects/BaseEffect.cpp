// Copyright © Too Many Eyes , 2022


#include "BaseEffect.h"

// Sets default values for this component's properties
UBBBaseEffect::UBBBaseEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBBBaseEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBBBaseEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBBBaseEffect::OnUse(TArray<AActor*> actors)
{
	return true;
}

