// Copyright © Too Many Eyes , 2022 - 2023


#include "BlightBrew/Gameplay/Tutorial/BBDialogueTrigger.h"

#include "Components/ShapeComponent.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"

ABBDialogueTrigger::ABBDialogueTrigger()
{
	bIsTriggered = false;

	DialogueComponent = CreateDefaultSubobject<UBBDialogueComponent>(TEXT("DialogueComponent"));
}

void ABBDialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABBDialogueTrigger::TriggerOverlapBegin);
}

void ABBDialogueTrigger::TriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsTriggered)
	{
		return;
	}

	if (ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(OtherActor))
	{
		if (DialogueComponent)
		{
			DialogueComponent->OnInteract(player);
			bIsTriggered = true;
		}
	}
}
