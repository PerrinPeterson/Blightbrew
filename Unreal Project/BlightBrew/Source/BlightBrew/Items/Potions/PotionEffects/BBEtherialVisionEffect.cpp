// Copyright © Too Many Eyes , 2022


#include "BBEtherialVisionEffect.h"
#include "Kismet/GameplayStatics.h"
//Blightbrew
#include "../../../Puzzle/BBRevealableActor.h"

bool UBBEtherialVisionEffect::OnUse(TArray<AActor*> actors)
{
	//Get all the actors of, and inheriting from, ABBRevealableActor
	TArray<AActor*> RevealableActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBRevealableActor::StaticClass(), RevealableActors);
	
	//Loop through all the actors
	for (AActor* actor : RevealableActors)
	{
		//Cast the actor to a RevealableActor
		ABBRevealableActor* RevealableActor = Cast<ABBRevealableActor>(actor);
		//If the actor is valid
		if (RevealableActor)
		{
			//Reveal the actor
			RevealableActor->RevealActor();
		}
	}
	//Set a timer to end the effects
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UBBEtherialVisionEffect::EndEffects, EffectTime);
	
	return true;
}

void UBBEtherialVisionEffect::EndEffects()
{
	//Get all the actors of, and inheriting from, ABBRevealableActor
	TArray<AActor*> RevealableActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBRevealableActor::StaticClass(), RevealableActors);

	//Loop through all the actors
	for (AActor* actor : RevealableActors)
	{
		//Cast the actor to a RevealableActor
		ABBRevealableActor* RevealableActor = Cast<ABBRevealableActor>(actor);
		//If the actor is valid
		if (RevealableActor)
		{
			//Hide the actor
			RevealableActor->HideActor();
		}
	}
}
